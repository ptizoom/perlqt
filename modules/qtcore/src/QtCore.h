#ifndef QT_H
#define QT_H

#include "smokeperl.h"
#include "smokehelp.h"

//#define Q_DECL_EXPORT __attribute__ ((visibility("default")))

#ifdef PERLQTDEBUG
SV* catArguments(SV** sp, int n);
SV* catCallerInfo( int count );
#endif
const char* get_SVt(SV* sv);
Q_DECL_EXPORT SV* getPointerObject(void* ptr);
int isDerivedFrom(Smoke *smoke, Smoke::Index classId, Smoke::Index baseId, int cnt);
int isDerivedFrom(Smoke *smoke, const char *className, const char *baseClassName, int cnt);
void mapPointer(SV *obj, smokeperl_object *o, HV *hv, Smoke::Index classId, void *lastptr);
void unmapPointer( smokeperl_object* o, Smoke::Index classId, void* lastptr);

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
