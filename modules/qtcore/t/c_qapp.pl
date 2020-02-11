#! perl   -I/usr/src/perlqt5/t 	-I/usr/src/perlqt5/bld/blib/lib 	-I/usr/src/perlqt5/bld/blib/arch  	-I/usr/src/perlqt5/modules/qtcore/lib  	-I/usr/src/perlqt5/modules/qtgui/lib -It -I../lib
# -I /home/christian/prj/ai/freeciv/bld/perl/blib/lib
BEGIN { 
    require tests;
    unless ($@) {
#	plan tests => ,
	# todo => [37..40],
    } else {
#	plan tests => 1;
	print "ok 1 # Skipped: no sourcefilter support\n";
	exit;
    }
}

END {
    done_testing(4);
}

#use Test::More tests => 3;

use QtCore;
use QtCore::debug qw(ambiguous); #PTZ200120
use QtGui;

$classes =  Qt::_internal::getClassList();
diag( @$classes);

$a=0;

$a = Qt::Application( \@ARGV );
$a = Qt::CoreApplication( \@ARGV );


# Test if the Qt::Application ctor works

eval { $a = Qt::Application( \@ARGV ) };

ok( !+$@, 'Qt::Application ctor' ) or diag( $@ );

# Test wether the global qApp object is properly set up

eval { qApp->libraryPaths() };

ok( !+$@, 'qApp properly set up' ) or diag( $@ );

# One second test of the event loop

Qt::Timer::singleShot( 300, qApp, SLOT 'quit()' );

ok( !qApp->exec, 'One second event loop' );
