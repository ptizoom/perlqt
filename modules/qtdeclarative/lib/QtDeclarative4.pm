#***************************************************************************
#                          QtDeclarative4.pm  -  QtDeclarative perl client lib
#                             -------------------
#    begin                : 06-19-2010
#    copyright            : (C) 2010 by Chris Burel
#    email                : chrisburel@gmail.com
# ***************************************************************************

#***************************************************************************
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU General Public License as published by  *
# *   the Free Software Foundation; either version 2 of the License, or     *
# *   (at your option) any later version.                                   *
# *                                                                         *
# ***************************************************************************

package QtDeclarative4::_internal;

use strict;
use warnings;
use QtCore;
use base qw(Qt::_internal);

sub init {
    foreach my $c ( @{getClassList()} ) {
        QtDeclarative4::_internal->init_class($c);
    }
    foreach my $e ( @{getEnumList()} ) {
        QtDeclarative4::_internal->init_enum($e);
    }
}

sub normalize_classname {
    my ( $self, $cxxClassName ) = @_;
    $cxxClassName = $self->SUPER::normalize_classname( $cxxClassName );
    return $cxxClassName;
}

package QtDeclarative4;

use strict;
use warnings;
use QtCore;

require XSLoader;

our $VERSION = '0.96';

QtCore::loadModule('QtDeclarative4', $VERSION);

QtDeclarative4::_internal::init();

1;

