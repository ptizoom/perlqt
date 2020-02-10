#pragma once

//TODO:PTZ200104 obsoleted should use SmokePerlBinding instead
#include "smokebinding.h"

#ifndef Q_DECL_EXPORT
#define Q_DECL_EXPORT
#endif

namespace PerlQt5 {

  //TODO:PTZ200104 using Binding = SmokePerl::SmokePerlBinding;
  
  class Q_DECL_EXPORT Binding : public SmokePerl::SmokePerlBinding {
  public:
    Binding(): SmokePerl::SmokePerlBinding() {}
    Binding(Smoke* s): SmokePerl::SmokePerlBinding(s) {}
    
    virtual void deleted(Smoke::Index /*classId*/, void* cxxptr);
    virtual bool callMethod(Smoke::Index method, void* ptr, Smoke::Stack args, bool isAbstract);
    virtual char* className(Smoke::Index classId);
  };

}

extern PerlQt5::Binding binding;


