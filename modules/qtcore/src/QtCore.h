#ifndef QT_H
#define QT_H

#include "smokeperl.h"
#include "smoke_types_qt4.h"

//#define Q_DECL_EXPORT __attribute__ ((visibility("default")))

#ifdef PERLQTDEBUG
SV* catCallerInfo( int count );
#endif

extern SV* sv_this;
extern HV* pointer_map;
extern int do_debug;


#if QT_VERSION >= 0x050000 //PTZ200104  in /qt5/QtWidgets/
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE



#if QT_DEPRECATED_SINCE(5, 0)
#warn "using  QT_DEPRECATED T qVariantValue"
#else

//
//template<typename T> typedef qVariantFromValue<T> qVariantValue<T>;
//PTZ200107 could have been qVariantSetValue
//#define qVariantValue qVariantFromValue
//typedef qVariantFromValue qVariantValue;



template<typename T>
inline QT_DEPRECATED T qVariantValue(const QVariant &variant)
{ return qvariant_cast<T>(variant); }
#endif


QT_END_NAMESPACE

#endif


#endif // QT_H
