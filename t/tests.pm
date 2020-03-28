#
# $Id$
#
# complementary test module allowing
# design of tests as the same time of insvestigating
# development
#
# $Log$
#

use Config;
use Env;
use DynaLoader;

use Devel::Peek;
use Data::Dumper;

use Digest::MD5 qw/md5 md5_hex md5_base64/;
use IO::String;
use IO::File;
use Data::Hexdumper qw/hexdump/ ;
use File::Temp qw/tempfile tempdir mktemp/;
use File::Path qw(make_path remove_tree);
use File::Basename;

use File::pushd;
use Tie::IxHash;
#use MIME::Lite::HTML;

use Storable;
use Archive::Zip qw( :ERROR_CODES );

eval {require credorc;};

BEGIN {
    use File::Spec;

    sub update_test_libs {
        my $t_libs = shift;
        my $blddir = shift;

=TODO find where is builddir abs_builddir
=TODO:CPM130921 $srcdir # $bldir # $archdir
=cut
        
        my $ldlibpthname         = $Config::Config{ldlibpthname} || 'LD_LIBRARY_PATH';
        my $ldlibpthname_defined = defined $Config::Config{ldlibpthname};
        my $pthsep = $Config::Config{path_sep} || ':';
	my @ld_library_path = split(/$pthsep/, $ENV{$ldlibpthname});
  
        my @dl_library_path    = (); 
        push(@dl_library_path, split(' ', $Config::Config{libpth}));

        #$ENV{LD_TRACE_LOADED_OBJECTS}=1;
        #$ENV{LD_DEBUG}='all';
	
	my @suffix_libs_path = ('.libs'
                                , 'blib/arch/auto'
                                , 'src/interfaces/perl_modular'
				, 'src'
				, 
             );


        my @libs_dir = ();
        foreach my $bld_basedir (@$blddir) {
            push(@libs_dir
                 , grep(-d
                        , map(File::Spec->catdir($bld_basedir, $_)
                              , @suffix_libs_path))
		 #, '/usr/local/lib' #PTZ191126 for PerlQt5  libsmokeperl.so
		 
		);
        }

        #TODO::PTZ140309 this needs to be run twice!!! only the second time it updates
        #$ENV{$ldlibpthname} = join($pthsep, @libs_dir, @dl_library_path, @ld_library_path);
        #print Dumper($ENV{$ldlibpthname});
        #unshift(@DynaLoader::dl_library_path, @libs_dir); 
        #or 
        my @L_libs_dir = map('-L' . $_, @libs_dir);      
        my @dl_resolve_using = &DynaLoader::dl_findfile(@L_libs_dir, @$t_libs);

	#PTZ191126 for PerlQt5  libsmokeperl.so installed in /usr/local/lib
        #push(@dl_resolve_using, &DynaLoader::dl_findfile(qw(-L/usr/local/lib -lsmokeperl)));
	

        print STDERR "tests::DynaLoader::dl_findfile=", Dumper(@dl_resolve_using);

        my @dl_resolve_using_d;
        #CPM140526 RTLD_LAZY || RTLD_NOW don't be lazy
        my $_dl_load_flag = 0x01;
        #CPM140526 does nothing?
        #push(@DynaLoader::dl_require_symbols, qw(luaopen_base genhash_str_copy_func));
        #push(@DynaLoader::dl_require_symbols, qw(servers_scan_begin announce));

        #load those libs
        foreach my $_lib  (@dl_resolve_using) {
            my $_lib_d = File::Basename->dirname($_lib);
            push(@dl_resolve_using_d,  $_lib_d);

            unshift(@DynaLoader::dl_library_path, $_lib_d)
                unless(grep($_lib_d, @DynaLoader::dl_library_path));

            my $libref =  &DynaLoader::dl_load_file($_lib, $_dl_load_flag) or
                print STDERR "Can't load '$_lib' : " . &DynaLoader::dl_error();

            if($libref) {
                push(@DynaLoader::dl_librefs, $libref);
                print STDERR "tests::DynaLoader::dl_librefs=", $_lib, '->'  , $libref, "\n";
            }
        }
        return \@dl_resolve_using;
    }
    
 

    use lib qw[
        ${HOME}/prj/qt/perlqt.git/perl/lib
        /home/christian/prj/qt/perlqt.git/perl/lib
	/usr/local/lib/perl5
    ];
    if($0 =~ qr#/usr/src/#) {
	my($p) = $0 =~ m#/usr/src/[^/]+/#g;        
	unshift(@INC, File::Spec->catdir($p, 'lib'));
    }
    if($0 =~ qr#prj/[^/]+/#) {
	my($p) = $0 =~ m#^.*/prj/[^/]+/#g;
	unshift(@INC, File::Spec->catdir($p, 'lib'));
    }
    #check lib is present in perldb tracing mode
    if($0 =~ qr#/usr/.*src/#) {
	my $i = 2;
	my $d = File::Basename->dirname($0);
	my $p = File::Spec->catdir($d, '..');
	while($i-- > 0) {
	    $d = File::Spec->catdir($p, 'lib');
	    if(-d $d) {
		unshift(@INC, $d);
		#use lib $d;
		last;
	    }
	    $p = File::Spec->catdir($p, '..');
	}
    }

    $ENV{PERL_DL_DEBUG} = 1;
    $ENV{abs_builddir} = File::Spec->catdir($ENV{HOME}, "prj/qt/perlqt.git/bld")
	unless(defined($ENV{abs_builddir}));
    my @blddir = (
	File::Spec->catdir($ENV{abs_builddir})
	, File::Spec->catdir($ENV{abs_builddir}, 'perl')
	, File::Spec->rel2abs('.')
	, File::Spec->rel2abs('..')
        );
#CPM140525 order matters
    #my $tlib = [ qw(modshogun lua5.1 lua5.1-c++ )];
    my $tlib = [ qw()];
    &update_test_libs($tlib, \@blddir);
    
    #&test_harness(0, 'blib/lib', 'blib/arch');  
}

sub ok {
	_base_dumper('ok', @_);
}
sub is($$;$) {
	_base_dumper('is', @_);
}
sub like($$;$) {
	_base_dumper('like', @_);
}
sub is_deeply {
	_base_dumper('is_deeply', @_);
}

sub use_ok {
	my $u = shift;
	$u = $u . '.pm';
	$u =~ s/::/\//g;
	require $u ,(@_);
}
sub cmp_ok {
	_base('cmp_ok', @_);
}
sub diag {
	_base('diag', @_);
}
sub done_testing {
	_base('done_testing', @_);
}
sub skip {
	_base('skip', @_);
}
sub _base {
	my $s = 'Test::More::' . shift;
	if($0 =~ qr/\.t$/) {
		&{$s}(@_);
	} else {
		print caller(), @_;
	}
}
sub _base_dumper {
	my $s = 'Test::More::' . shift;
	if($0 =~ qr/\.t$/) {
		&{$s}(@_);
	} else {
		print caller(), Dumper(@_);
	}
}

if($0 =~ qr/\.t$/) {
    require Test::More;
    foreach
	$s
	(qw/ok is diag done_testing use_ok skip like cmp_ok is_deeply/)
    {
	undef *{$s};
	*{$s} = \&{'Test::More::' . $s};
    }
}

@search_path_d  = ('.', 'doc', '../doc', 't', '../t');
$d_t = (-d 't' ? 't/' : '');
$test_jump = "\n" x 3;
$uri =  $d_t . '';
@f_directories = ( $uri	);

$stored_f = $d_t . '_searched.pdb';

%strd_pb = (
    search =>  $d_t . '_searched.pdb'
    , scrap_google =>  $d_t . '_scrapped.pdb'
    , spider =>  $d_t . 'pl_p.pdb'
    , dbf => $d_t . 'patent_dbi.db'
    );




$pl_pl_e = {
      };



# TODO::CPM120821 a better cache 
sub retrieve_tests {
    my $f = shift;
    if(-f $strd_pb{scrap_}) {
	$r = $f->{scraps} = retrieve($strd_pb{scrap_});
    } else {
	if(-f $strd_pb{search}) {
	    $f->{searched} = retrieve($strd_pb{search});
	} else {
	    $r = $f->search::get(q(Altherma panne));
	    store(\@{$f->{searched}}, $strd_pb{search});
	}
	$r = $f->scrap::main(122);
	store(\@{$r}, $strd_pb{scrap_});
    }
}



sub start_a_server_ {
    $ip = system(q[freeciv-server]);
#TODO:PTZ140601...PTZ160107 t050_server_fire_up.t


    
}
 
sub how_many_hosts {
    use NetAddr::IP;

    my $hosts = 0;
    push @space, new NetAddr::IP->new($_)
        for <DATA>;
    $hosts += $_->num for @space;
    print "You have $hosts\n";
}

@args = qw(
        );

1;

__DATA__
10.0.0.0/16
172.16.0.0/24


__END__

=pod

	my $found = 0;
	foreach my $p (@ld_library_path) {
	    if(-f  File::Spec->catfile($p, $t_libs[0] . '.so')) {
		$found = 1;
		last;
	    }
	}
        unless($found) {
            $ENV{$ldlibpthname} = join($pthsep, @libs_dir, @blddir, @ld_library_path);
            print Dumper($ENV{$ldlibpthname});
        }

 
        $found = 0;
        foreach my $p (@INC) {
            if(-f File::Spec->catfile($p, $t_libs[0] . '.pm')) {
                $found = 1;
                last;
            }
        }
        unless($found) {#unshift(@INC, $d);
            unshift(@INC, @libs_dir);
            #use lib (@libs_dir);#PTZ121030 does not work
        }

=cut



=pod _Freeciv.bs

~/prj/ai/freeciv/bld/perl/blib/arch/auto/BOT/Freeciv/Freeciv.bs


my $flags = $modulename->dl_load_flags;
my @names = qw(freeciv-srv freeciv botfreeciv);
my @filepaths = dl_findfile(@names);
my $libref;
foreach my $_lib  (@filepaths) {
    $libref =  &dl_load_file($_lib, $flag);
    push(@dl_librefs, $libref);
}
print STDERR "BS: $bs ($^O, $dlsrc)\n";


=cut









print mkstr() . "\n";
my $str = mkstr();
print Dump($str),"\n\n";


my $arr = mkarr();
print ref($arr) . "\n";
print Dump($arr) . "\n";

@dl_resolve_using = dl_findfile(qw(-L/usr/local/lib -lsmokeperl));
