#ifndef SMOKEPERL_QTCORE_HANDLERS
#define SMOKEPERL_QTCORE_HANDLERS

#include "handlers.h"

using  TypeHandler = SmokePerl::TypeHandler;

extern TypeHandler qtcore_typeHandlers;

void marshall_QString(SmokePerl::Marshall* m);

#endif
