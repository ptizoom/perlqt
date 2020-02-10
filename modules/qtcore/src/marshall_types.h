// This file contains the class declarations of the various method call
// classes.


//TODO::PTZ200104 it is in virtualmethodcall.cpp
#ifndef MARSHALL_TYPES_H
#define MARSHALL_TYPES_H

#include "QtCore/QList"
#include "QtCore/QObject"
#if 0
extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
  //#include "ppport.h"
}
#endif
#include "marshall_qt4.h"
#include "binding_qt4.h" // for definition of PerlQt4::Binding
#include "smokeperl.h" // for smokeperl_object
#include "methodcall.h"
#include "virtualmethodcall.h"

#include "invokeslot.h"


void smokeStackToQtStack(Smoke::Stack stack, void ** o, int start, int end, QList<MocArgument*> args);
void smokeStackFromQtStack(Smoke::Stack stack, void ** _o, int start, int end, QList<MocArgument*> args);

namespace PerlQt5 {

// #if 0 //_PTZ200205 //SmokePerl::VirtualMethodCall::ReturnValue is private
//   class Q_DECL_EXPORT MethodReturnValueBase
//     : public SmokePerl::VirtualMethodCall::ReturnValue
//   //    public Marshall
//   {
// public:
//     MethodReturnValueBase(Smoke *smoke, Smoke::Index methodIndex, Smoke::Stack stack)
//       : SmokePerl::VirtualMethodCall::ReturnValue(){};
//     MethodReturnValueBase(Smoke::ModuleIndex methodId, Smoke::Stack stack, SV* returnValue);
 
//     const Smoke::Method &method();
//     Smoke::StackItem &item();
//     Smoke *smoke();
//     SmokeType type();
//     void next();
//     bool cleanup();
//     void unsupported();
//     SV* var();
// protected:
//     Smoke *_smoke;
//     Smoke::Index _methodIndex;
//     Smoke::Stack _stack;
//     SV *_retval;
//     SmokeType _type;

// };
  
// class Q_DECL_EXPORT VirtualMethodReturnValue
//   : public SmokePerl::VirtualMethodCall, MethodReturnValueBase {

//  public:
//     VirtualMethodReturnValue(Smoke *smoke, Smoke::Index meth, Smoke::Stack stack, SV* retval);
    
//     : VirtualMethodCall(Smoke::ModuleIndex methodId, Smoke::Stack stack, SV* self, GV* gv);
    
//     //Marshall::Action action();
// };

// class Q_DECL_EXPORT MethodReturnValue : public MethodReturnValueBase {
// public:
//     MethodReturnValue(Smoke *smoke, Smoke::Index meth, Smoke::Stack stack);
//     MethodReturnValue(Smoke *smoke, Smoke::Stack stack, SmokeType type);
//     //PTZ200207 Marshall::Action action();
// };

// class Q_DECL_EXPORT SlotReturnValue : public Marshall {
//     QList<MocArgument*> _replyType;
//     Smoke::Stack _stack;
//     SV * _result;
// public:
//     SlotReturnValue(void ** o, SV * result, QList<MocArgument*> replyType);
//     ~SlotReturnValue();
//     Smoke::StackItem &item();
//     Smoke *smoke();
//     SmokeType type();
//     Marshall::Action action();
//     void next();
//     bool cleanup();
//     void unsupported();
//     SV* var();
// };
// #endif //SmokePerl::VirtualMethodCall::ReturnValue is private

#if 1
  using MethodCallBase = SmokePerl::MethodCall;
#else
  class Q_DECL_EXPORT MethodCallBase
    : public SmokePerl::MethodCall //, Marshall
  {
  public:
    MethodCallBase(Smoke *smoke, Smoke::Index meth) {
      // dXSARGS; dXCPT;    HV* stash = CvSTASH(cv);
      Smoke::ModuleIndex _mi(smoke, meth);
      SV** _argv(0);      //m_args = m_methodId.smoke->argumentList + m_methodRef.args;(methodId.smoke->methods[methodId.index]
      smokeperl_object* _o = alloc_smokeperl_object(false, _mi, nullptr);      
      SV*  _s(&PL_sv_undef);
      if (_o) {
	std::string retclassname(_mi.smoke->classes[_mi.index].className);    
	_s = set_obj_info(retclassname.c_str(), _o);	
      }
      SmokePerl::MethodCall::MethodCall(_mi, _s, _argv);
    }
    
    //MethodCallBase(Smoke *smoke, Smoke::Index method, Smoke::Stack stack);
//     ////PTZ200207 dont use...
// #if 0
//     Smoke *smoke();
//     SmokeType type();
//     Smoke::StackItem &item();
//     const Smoke::Method &method();
//     virtual int items() = 0;
//     virtual void callMethod() = 0;
//     void next();
//     void unsupported();

// protected:
//     Smoke *_smoke;
//     Smoke::Index _method;
//     Smoke::Stack _stack;
//     int _cur;
//     Smoke::Index *_args;
//     bool _called;
//     SV **_sp;
//     virtual const char* classname();
// #endif
  };
#endif
#if _oldqt4 //VirtualMethodCall
  class Q_DECL_EXPORT VirtualMethodCall
    : public SmokePerl::VirtualMethodCall, MethodCallBase
{
public:
    VirtualMethodCall(Smoke *smoke, Smoke::Index meth, Smoke::Stack stack, SV *obj, GV *gv);
    ~VirtualMethodCall();
    Marshall::Action action();
    SV *var();
    int items();
    void callMethod();
    bool cleanup();

private:
    GV *_gv;
    SV *_savethis;
};
#else
  //PTZ200120
  using VirtualMethodCall = SmokePerl::VirtualMethodCall;
#endif


  
class Q_DECL_EXPORT MethodCall
//  : private MethodCallBase
  : public MethodCallBase
{
 private:
  
  SV* _smokeperl_object_SV(smokeperl_object *call_this) {
    SmokePerl::Object* _o = SmokePerl::ObjectMap::instance().get(call_this);
    SV* _self(&PL_sv_undef);
    if (_o) {_self = _o->sv;}
    return _self;
  }

public:
  //MethodCall(Smoke *smoke, Smoke::Index methodIndex, smokeperl_object *call_this, SV **sp, int items = 0);
  MethodCall(Smoke *smoke, Smoke::Index methodIndex, smokeperl_object *call_this, SV **_sp, int items)
    : MethodCallBase(
		     Smoke::ModuleIndex(smoke, methodIndex)
		     , _smokeperl_object_SV(call_this)
		     , _sp)
  {
    // Smoke::ModuleIndex _mi(smoke, method);
    // SmokePerl::Object* _o = SmokePerl::ObjectMap::instance().get(call_this);
    // SV* _self = _o->sv;
    // MethodCallBase(_mi, _self, _sp)
  }
    
  // MethodCall(Smoke::ModuleIndex mi, SV* self, SV** argv):;


//     ~MethodCall();
//     Marshall::Action action();
//     SV *var();

// #if _oldqt4 // taken from SmokePerl::Marshall
//     inline void callMethod() {
//         if( _called )
//             return;
//         _called = true;
//         Smoke::ClassFn fn = _smoke->classes[method().classId].classFn;
//         void *ptr = 0;
// #if _oldqt4	
//         if (_this->ptr != 0) {
//             const Smoke::Class &cl = _smoke->classes[method().classId];

//             ptr = _this->smoke->cast(
//                 _this->ptr,
//                 _this->classId,
//                 _this->smoke->idClass(cl.className, true).index
//             );
//         }
// #else
// 	SmokePerl::Object* obj = SmokePerl::Object::fromSV(m_self);
// 	if (obj != nullptr) {
// 	  ptr = obj->value;
// 	}	
// #endif
//         // Call the method
//         (*fn)(method().method, ptr, _stack);

//         // Tell the method call what binding to use
//         if (method().flags & Smoke::mf_ctor) {
//             Smoke::StackItem s[2];
//             s[1].s_voidp = perlqt_modules[_smoke].binding;
//             (*fn)(0, _stack[0].s_voidp, s);
//         }

//         // Marshall the return value
//         MethodReturnValue callreturn( _smoke, _method, _stack );

//         // Save the result
//         _retval = callreturn.var();
//     }
// #endif

    
//     int items(); // What's this?
//     bool cleanup();

// private:
//     smokeperl_object *_this;
//     SV **_sp;
//     int _items;
//     SV *_retval;
//     const char *classname();
};

class Q_DECL_EXPORT MarshallSingleArg : public MethodCallBase {
public:
    MarshallSingleArg(Smoke *smoke, SV* sv, SmokeType type);
//     ~MarshallSingleArg();
//     Marshall::Action action();
//     SV *var();

//     void callMethod() {}

//     int items(); // What's this?
//     bool cleanup();

//     SmokeType type();
//     Smoke::StackItem &item();

// private:
//     SV *_sv;
//     SV *_retval;
//     SmokeType _type;
//     const char *classname();
};


using InvokeSlot = PerlQt5::InvokeSlot;
//InvokeSlot(const QMetaMethod& method, SV* self, void** a, SV* code)

// class Q_DECL_EXPORT InvokeSlot : public Marshall {
// public:
//     InvokeSlot(SV* call_this, char* methodname, QList<MocArgument*> args, void** a);
//     ~InvokeSlot();
//     Marshall::Action action();
//     const MocArgument& arg();
//     SmokeType type();
//     Smoke::StackItem &item();
//     SV* var();
//     Smoke *smoke();
//     void callMethod();
//     void unsupported();
//     void next();
//     bool cleanup();
//     void copyArguments();

// protected:
//     char* _methodname;
//     QList<MocArgument*> _args;
//     int _cur;
//     bool _called;
//     Smoke::Stack _stack;
//     int _items;
//     SV** _sp;
//     SV* _this;
//     void** _a; // The Qt4 metacall stack
// };

class Q_DECL_EXPORT EmitSignal : public Marshall {
public:
    EmitSignal(QObject *obj, const QMetaObject *meta, int id, int items, QList<MocArgument*> args, SV** sp, SV* retval);
    Marshall::Action action();
    const MocArgument& arg();
    SmokeType type();
    Smoke::StackItem &item();
    SV* var();
    Smoke *smoke();
    void callMethod();
    void unsupported();
    void next();
    bool cleanup();
    void prepareReturnValue(void** o);

protected:
    QList<MocArgument*> _args;
    int _cur;
    bool _called;
    Smoke::Stack _stack;
    int _items;
    SV** _sp;
    QObject *_obj;
    const QMetaObject *_meta;
    int _id;
    SV* _retval;
};

} // End namespace PerlQt4

#endif // MARSHALL_TYPES_H
