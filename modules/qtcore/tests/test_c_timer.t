#! perl   -I/usr/src/perlqt5/t 	-I/usr/src/perlqt5/bld/blib/lib 	-I/usr/src/perlqt5/bld/blib/arch  	-I/usr/src/perlqt5/modules/qtcore/lib  	-I/usr/src/perlqt5/modules/qtgui/lib -It -I../lib
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
    done_testing(2);
}


#use Test::More tests => 4-1;

use PerlQt5::QtCore qw(SIGNAL SLOT);

package MyTimer;
use base qw(PerlQt5::QtCore::QTimer);

sub mytimeout: Slot() {
    my ($self, $i) = @_;
    $self->timeout();
}


package MyObject;
use PerlQt5::QtCore;
use base qw(PerlQt5::QtCore::QObject);
use Test::More;

our $t_prev = time();
our $dt = 2000;
our $step = 0;


sub new {
    my $class = shift;
    my $self = $class->SUPER::new(@_);    
    $self->{timer} = PerlQt5::QtCore::QBasicTimer->new();
    $self->{step} = 0;
    $self->{t_prev} = time();
    $self->{timer}->start($dt, $self);
}


sub timerEvent {
    my ($self, $event) = @_;
    if ($event->timerId() == $self->{timer}->timerId()) {
	$self->{t_now} = time();
	unless ($self->{step}) { $self->{t_prev} = time(); }
        if(++ $self->{step} > 3) {
	    my $_dt = $self->{t_now} - $self->{t_prev};
	    
	    ok($_dt > $dt || $_dt == 0
	       , 'myQObject::timerEvent called at ' . $dt . 'ms interval after ' . $_dt . 's');
	    
	    #$self->{timer}->stop();
	    #QMetaObject::invokeMethod(thread, "quit", $Qt::QueuedConnection);
	    $self->metaObject()
		->invokeMethod($self->thread()
			       , 'quit()'
			       , &PerlQt5::QtCore::Qt::QueuedConnection()
		);
	    #$self->parent()->quit();
	}
    } else {
        #QWidget::timerEvent(event);
    }
}


sub mySlot : Slot() {
    my ($self) = @_;
    #print "mySlot\n";
    #ok('Slot called');    
    my $t_now = time();
    my $_dt = $t_now - $t_prev;
    ok($_dt > $dt || $_dt == 0
       , 'MyObject::mySlot called at ' . $dt . 'ms interval after ' . $_dt . 's')
	or diag ('my QObject called at ' . $_dt . 'ms interval');
    
    unless ($self->{step}) { $t_prev = time(); }
    #$self->quit() if ($cnt++ > 2);
    if(++ $self->{step} > 3) {
       	#$self->{timer}->stop();
	#my $mo = $self->metaObject();
	$self->metaObject()
	    ->invokeMethod($self->thread()
			   , 'quit()'
			   , &PerlQt5::QtCore::Qt::QueuedConnection()
	    );
    }
}


package main;

my $app = PerlQt5::QtCore::QCoreApplication->new(\@ARGV);

# Test if the Qt::Application ctor works
#ok( !+$@, 'PerlQt5::QtCore::QApplication ctor' ) or diag( $@ );
# Test wether the global qApp object is properly set up
# One second test of the event loop
# QTimer *timer = new QTimer(this);
#    connect(timer, SIGNAL(timeout()), this, SLOT(processOneThing()));
#    timer->start();
#my $t = MyTimer->new($obj);

my $obj = MyObject->new($app);

#my $obj = MyObject->new();
my $t = MyTimer->new($app);


# connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
#   timer->start(1000);
#my $r = $obj->connect($t, SIGNAL 'timeout()',$obj, SLOT 'mySub(int)');
#QObject::connect: Incompatible sender/receiver arguments
#        MyTimer::timeout() --> MyObject::mySub(int)
#0  PerlQt5::QtCore::QMetaObject::Connection=HASH(0x5589914f9548)
#     empty hash
#QObject::connect: No such signal MyTimer::mytimeout(int)

my $signal = $t->can('timeout');
#isa_ok($signal, 'PerlQt5::QtCore::Signal');


my $r = $app->connect($t, SIGNAL 'timeout()', $obj, SLOT 'mySlot()');




#my $r = $obj->connect($t, SIGNAL 'timeout()', $obj, SLOT 'mySlot()');

ok( !+$@, 'connect timeout event with a QObject properly set up' ) or diag( $@ );

#!+$@




#$r = $obj->connect($t, SIGNAL 'mytimeout(int)',$obj, SLOT 'mySub(int)'); 
#void QTimer::start(std::chrono::milliseconds msec)

$MyObject::t_prev = time();
$r = $t->start(2500);
$MyObject::dt = $t->interval();

#diag(time() - $MyObject::t_prev . 'ms main::mark');
#$t->setInterval(5000);
#$MyObject::dt = $t->interval();

diag(time() - $MyObject::t_prev . 'ms main::mark');
#ok( !$app->exec, 'QTimer multi shot One second event loop' );

$app->processEvents();
ok( !+$@, 'processEvents done ok' ) or diag( $@ );

#
#$t = PerlQt5::QtCore::QTimer::
#$r = $t->singleShot(30, $app, SLOT 'quit()');

#my $t0 = $MyObject::t_prev = time();
#ok( !$app->exec, 'singleShot One second event loop' );
#my $t1 = time();

#is($t1 - $t0 < 300, 'singleShot One second event')
#    or diag ($t1 - $t0, 'ms spent');


