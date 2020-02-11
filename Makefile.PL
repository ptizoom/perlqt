#!/usr/bin/perl

use strict;
use Config;
use File::pushd;

use ExtUtils::MakeMaker qw($Verbose &WriteMakefile);
use ExtUtils::Constant qw(WriteConstants);
$ExtUtils::MakeMaker::Verbose=10;
use ExtUtils::Mkbootstrap;

my ($prefix, $sitearch, $qmake) = ($Config{prefix}, $Config{sitearch});
my @cmakeArgs;
foreach my $arg (@ARGV) {
    my $key = $arg;
    my $value = $key;
    $key =~ s/=.*//g;
    $value =~ s/^[^=]*=//g;
    if ($key eq 'PREFIX' or $key eq 'INSTALL_BASE') {
        $prefix = $value;
        $sitearch = "$prefix";
    }
    elsif ($key eq 'QMAKE') {
        $qmake = $value;
    }
    else {
        push @cmakeArgs, $arg;
    }
}

my @args;
#PTZ191124
push @args, '..';
push @args, '-DCMAKE_BUILD_TYPE=Debug';

#push @args, '-DCMAKE_BUILD_TYPE=Release';

my $pathsearch = ":";
my $cmakesearch = "cmake";
if($^O =~ /win/i && $^O !~ /cygwin/i){
    $pathsearch = ";";
    $cmakesearch = "cmake.exe";
}
push @args, "-DCMAKE_INSTALL_PREFIX=$prefix" if $prefix;
push @args, "-DQT_QMAKE_EXECUTABLE=$qmake" if $qmake;
push @args, "-DCUSTOM_PERL_SITE_ARCH_DIR=$sitearch" if $sitearch;
push @args, @cmakeArgs;

if ( eval "require Alien::SmokeQt" ) {
    push @args, "-DSmoke_DIR=".Alien::SmokeQt->prefix()."/share/smoke/cmake";
    push @args, "-DCMAKE_MODULE_PATH=".Alien::SmokeQt->prefix()."/share/smoke/cmake";
}

# Make sure we have a cmake executable
my $cmake;
foreach my $path ( split m/$pathsearch/, $ENV{PATH} ) {
    if ( -e "$path/".$cmakesearch ) {
        $cmake = "$path/".$cmakesearch;
        last;
    }
}
if ( !$cmake ) {
    die 'You must have cmake installed to compile PerlQt.';
}

do {
    (-d 'bld') || mkdir('bld');
    my $_d = pushd( 'bld' );
    exit system('cmake', @args);
};
