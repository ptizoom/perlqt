#pragma once

class QString;
class QByteArray;

#include "marshall_qt4.h"
#include "smoke_types_qt4.h"

#include "smokeperl.h"
#include "qtcore_handlers.h"

//TODO::PTZ200317 check with Smoke::Type
// or better...: std::unordered_map<std::string, SmokePerl::Marshall::HandlerFn> qtcore_typeHandlers;
// struct TypeHandler {
//     const char* name;
//     Marshall::HandlerFn fn;
// };
//using TypeHandler=SmokePerl::TypeHandler;

// SV destruction methods
int smokeperl_free(pTHX_ SV* sv, MAGIC* mg);
void invoke_dtor(smokeperl_object* o);

// The magic virtual table that tells sv's to call smokeperl_free when they're
// destroyed
//PTZ200207  extern struct mgvtbl vtbl_smoke; within ObjectMap::

Q_DECL_EXPORT void *construct_copy(smokeperl_object *o);


//PTZ200317const marshall_it(Marshall*) = (void*)(SmokePerl::Marshall*) SmokePerl::marshall_PrimitiveRef< T>;
//no matches converting function ‘marshall_PrimitiveRef’ to type ‘void (* const)(class SmokePerl::Marshall*)’
template <class T>
const auto marshall_it = SmokePerl::marshall_PrimitiveRef<T>;
//void (* const)(class SmokePerl::Marshall*) marshall_it = SmokePerl::marshall_PrimitiveRef<T>;

const auto marshall_charP_array = SmokePerl::marshall_CharPArray;


//PTZ200207 done inside marshall itself!void marshall_basetype(Marshall* m);
const auto marshall_basetype    = SmokePerl::marshall_basetype;


//PTZ200318 in qtcore_handlers.cpp and with args void marshall_QString(SmokePerl::Marshall* m)
//PTZ200207void marshall_QString(Marshall* m);
//PTZ200207void marshall_QStringList(Marshall* m);
//PTZ200207 void marshall_unknown(Marshall *m);
const auto marshall_unknown        = SmokePerl::marshall_unknown;

//PTZ200207 void marshall_void(Marshall* m);
const auto marshall_void        = SmokePerl::marshall_void;
const auto marshall_voidP_array = SmokePerl::marshall_VoidPArray;



QString* qstringFromPerlString( SV* perlstring );
QByteArray* qbytearrayFromPerlString( SV* perlstring );
SV* perlstringFromQString( QString * s );
SV* perlstringFromQByteArray( QByteArray * s );

//PTZ200213 extern HV* type_handlers;
extern TypeHandler Qt_handlers;

//PTZ200318 aka SmokePerl::Marshall::installHandlers(const TypeHandler& handlers)
//Q_DECL_EXPORT void install_handlers(TypeHandler const& h);
//PTZ200318 Marshall::HandlerFn getMarshallFn(const SmokeType& type);

const auto install_handlers = SmokePerl::Marshall::installHandlers;
const auto getMarshallFn = SmokePerl::Marshall::getMarshallFn;




#define UNTESTED_HANDLER(name) fprintf( stderr, "The handler %s has no test case.\n", name );

