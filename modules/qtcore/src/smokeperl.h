#pragma once
#include "QtCore/QHash"
#include "binding_qt4.h"
//#include "smoke.h"
#include "smoke_types_qt4.h"
#include "smokeobject.h"

struct smokeperl_object : public SmokePerl::Object {
  
  smokeperl_object(void*& _p
		   , const Smoke::ModuleIndex& _mi
		   , SmokePerl::Object::ValueOwnership _own)
    : SmokePerl::Object::Object(_p, _mi, _own) {}

  //bool allocated; validCppObject isValid()
  //PTZ200120 ?it could be a perl-allocated... but this is redundant? 
  //bool allocated = false; = validCppObject
  inline bool allocated() {return isValid();}

  //smokeperl_object *alloc_smokeperl_object(bool allocated, Smoke * smoke, int classId, void * ptr);
  
  //Smoke* smoke; //PTZ200120 ? not sure of equiv. ie.  (Smoke::ModuleIndex& classId).smoke;
  //int classId;
  //void* ptr; to value or  obj->cast(classId);  
  inline void* ptr() {return value;}

  //using ptr = value;
  
  Smoke* smoke() {return classId.smoke;}

  //inline void* cast(const Smoke::ModuleIndex targetId) const ;
  
  inline void* cast(const char* ItemSTR) const {
    //Smoke::ModuleIndex targetId = classId.smoke->idClass(ItemSTR);
    //Smoke* _s = classId.smoke;
    return SmokePerl::Object::cast(classId.smoke->idClass(ItemSTR));
  }
};

typedef const char* (*ResolveClassNameFn)(smokeperl_object * o);
typedef void (*ClassCreatedFn)(const char* package, SV* module, SV* klass);
typedef bool (*MarshallSlotReturnValueFn)(Smoke::ModuleIndex classId, void** o, Smoke::Stack stack);


//TODO:PTZ200210 
struct PerlQtModule {
    const char *name;
    ResolveClassNameFn resolve_classname;
    ClassCreatedFn class_created;
    PerlQt5::Binding *binding;
    MarshallSlotReturnValueFn slot_returnvalue;
};

extern Q_DECL_EXPORT QHash<Smoke*, PerlQtModule> perlqt_modules;

inline smokeperl_object* sv_obj_info(SV* sv) { // ptr on success, null on fail
#if qt4_PTZ200120
    if(!sv || !SvROK(sv) || !(SvTYPE(SvRV(sv)) == SVt_PVHV || SvTYPE(SvRV(sv)) == SVt_PVAV))
        return 0;
    SV *obj = SvRV(sv);
    MAGIC *mg = mg_find(obj, '~');
    if(!mg ){//|| mg->mg_virtual != &vtbl_smoke) {
        // FIXME: die or something?
        return 0;
    }
    smokeperl_object *o = (smokeperl_object*)mg->mg_ptr;
    return o;
#else
    return (smokeperl_object*)SmokePerl::Object::fromSV(sv);
#endif
}

// keep this enum in sync with lib/Qt4/debug.pm
enum QtDebugChannel {
    qtdb_none = 0x00,
    qtdb_ambiguous = 0x01,
    qtdb_autoload = 0x02,
    qtdb_calls = 0x04,
    qtdb_gc = 0x08,
    qtdb_virtual = 0x10,
    qtdb_verbose = 0x20,
    qtdb_signals = 0x40,
    qtdb_slots = 0x80,
};

enum MocArgumentType {
    xmoc_ptr,
    xmoc_bool,
    xmoc_int,
    xmoc_uint,
    xmoc_long,
    xmoc_ulong,
    xmoc_double,
    xmoc_charstar,
    xmoc_QString,
    xmoc_void
};

struct MocArgument {
    // smoke object and associated typeid
    SmokeType st;
    MocArgumentType argType;
};

