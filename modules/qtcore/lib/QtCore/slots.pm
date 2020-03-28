package QtCore::slots;
#
# Proposed usage:
#
# use QtCore::slots changeSomething => ['int'];
#

use strict;
use warnings;
use Carp;
use QtCore;
use Scalar::Util qw(looks_like_number);
use PerlQt5::QtCore;
use PerlQt5::QtCore::Slot;

our $VERSION = 0.60;

sub import {
    no strict 'refs';
    my $self = shift;
    croak "Odd number of arguments in slot declaration" if @_%2;
    my $caller = $self eq 'QtCore::slots' ? (caller)[0] : $self;
    my @slots = @_;
    my $meta = \%{ $caller . '::META' };

    # The perl metaObject holds info about signals and slots, inherited
    # sig/slots, etc.  This is what actually causes perl-defined sig/slots to
    # be executed.
    *{ "${caller}::metaObject" } = sub {
        return Qt::_internal::getMetaObject($caller);
    } unless defined &{ "${caller}::metaObject" };

 
    my $_metaObject = &{ "${caller}::metaObject" } ();
    



    my $public = 1;

    my %publicprivate;
    @publicprivate{qw(public private)} = undef;

    for ( my $i = 0; $i < @slots; $i += 2 ) {
        my $fullslotname = $slots[$i];
        my $slotargs = $slots[$i+1];

	#PTZ200313 does everything.... !
	&PerlQt5::QtCore::_internal::addSlot($_metaObject, $fullslotname, $slotargs);

	#PTZ200317 might not be nescessary ?
        if ( exists $publicprivate{$fullslotname} &&
            looks_like_number( $slotargs ) &&
            $slotargs > 0 ) {
            if ( $fullslotname eq 'public' ) {
                $public = 1;
            }
            else {
                $public = 0;
            }
            next;
        }

        # Determine the slot return type, if there is one
        my @returnParts = split / +/, $fullslotname;
        my $slotname = pop @returnParts; # Remove actual method name
        my $returnType = @returnParts ? join ' ', @returnParts : undef;

        # Build the signature for this slot
        my $signature = join '', ("$slotname(", join(',', @{$slotargs}), ')');

        # Normalize the signature, might not be necessary
        $signature = Qt::MetaObject::normalizedSignature(
            $signature )->data();

        my $slot = {
            name => $slotname,
            signature => $signature,
            returnType => $returnType,
            public => $public,
        };

        push @{$meta->{slots}}, $slot;
	#PTZ200317 do we need the above...? MOC is not done	
    }
       #PTZ200313     Qt::_internal::installqt_metacall( $caller ) unless defined &{$caller."::qt_metacall"};
    #need metaobject...
    {
    #	my $meta_object = &{ "${caller}::metaObject" } ();
    	&Qt::_internal::installqt_metacall($meta_object);
	croak( ${caller} . ":: metaObject() has not been declared by ...::addSlot ");
    } unless defined &{$caller."::qt_metacall"};

}

1;
