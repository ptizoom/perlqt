#!/usr/bin/perl

package NetworkGoogleSuggestTest;

use strict;
use warnings;

use QtCore;
use QtGui4;
use QtTest4 qw( QVERIFY );
use SearchBox;
use QtCore::isa qw(Qt::Object);
use QtCore::slots
    private => 1,
    initTestCase => [],
    tryTyping =>[];
use Test::More;

sub NEW {
    my ($class, $parent) = @_;
    $class->SUPER::NEW();
}

sub tryTyping {
    my $searchEdit = this->{searchEdit};
    my $string = 'The quick brown fox jumped over';
    Qt::Test::keyClicks( $searchEdit, $string, Qt::NoModifier(), 300 );

    pass( 'Typing' );
}

sub initTestCase {
    my $searchEdit = SearchBox();
    $searchEdit->show();
    Qt::Test::qWaitForWindowShown( $searchEdit );
    this->{searchEdit} = $searchEdit;
    pass( 'Window shown' );
}

package main;

use strict;
use warnings;

use QtCore;
use QtGui4;
use QtTest4 qw(QTEST_MAIN);
use NetworkGoogleSuggestTest;
use Test::More tests => 2;

exit QTEST_MAIN('NetworkGoogleSuggestTest');
