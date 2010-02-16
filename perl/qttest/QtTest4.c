/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.18_02 from the
 * contents of QtTest4.xs. Do not edit this file, edit QtTest4.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "QtTest4.xs"
/***************************************************************************
                          QtTest4.xs  -  QtTest perl extension
                             -------------------
    begin                : 07-12-2009
    copyright            : (C) 2009 by Chris Burel
    email                : chrisburel@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <QHash>
#include <QList>
#include <QtDebug>

#include <iostream>

// Perl headers
extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "ppport.h"
}

#include <smoke/qttest_smoke.h>

#include <smokeperl.h>
#include <handlers.h>

extern QList<Smoke*> smokeList;

const char*
resolve_classname_qttest(smokeperl_object * o)
{
    return perlqt_modules[o->smoke].binding->className(o->classId);
}

extern TypeHandler QtTest4_handlers[];

static PerlQt4::Binding bindingtest;

#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#line 63 "QtTest4.c"

XS(XS_QtTest4___internal_getClassList); /* prototype to pass -Wmissing-prototypes */
XS(XS_QtTest4___internal_getClassList)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 0)
       Perl_croak(aTHX_ "Usage: %s(%s)", "QtTest4::_internal::getClassList", "");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	SV *	RETVAL;
#line 56 "QtTest4.xs"
        AV* classList = newAV();
        for (int i = 1; i < qttest_Smoke->numClasses; i++) {
            if (qttest_Smoke->classes[i].className && !qttest_Smoke->classes[i].external)
                av_push(classList, newSVpv(qttest_Smoke->classes[i].className, 0));
        }
        RETVAL = newRV_noinc((SV*)classList);
#line 85 "QtTest4.c"
	ST(0) = RETVAL;
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_QtTest4); /* prototype to pass -Wmissing-prototypes */
XS(boot_QtTest4)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    char* file = __FILE__;

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    XS_VERSION_BOOTCHECK ;

        newXS("QtTest4::_internal::getClassList", XS_QtTest4___internal_getClassList, file);

    /* Initialisation Section */

#line 70 "QtTest4.xs"
    init_qttest_Smoke();
    smokeList << qttest_Smoke;

    bindingtest = PerlQt4::Binding(qttest_Smoke);

    PerlQt4Module module = { "PerlQtTest4", resolve_classname_qttest, 0, &bindingtest  };
    perlqt_modules[qttest_Smoke] = module;

    install_handlers(QtTest4_handlers);

#line 124 "QtTest4.c"

    /* End of Initialisation Section */

    if (PL_unitcheckav)
         call_list(PL_scopestack_ix, PL_unitcheckav);
    XSRETURN_YES;
}

