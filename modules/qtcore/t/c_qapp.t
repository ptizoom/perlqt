use Test::More tests => 3;

use QtCore;
use QtCore::debug qw(ambiguous); #PTZ200120
use QtGui;
#use Qt;	
#use Qt::GlobalSpace;

$classes =  Qt::_internal::getClassList();
diag( @$classes);

$a=0;

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
