#include <functional>
#include <reflectionzeug/Object.h>
#include <reflectionzeug/Variant.h>
#include "scriptzeug/BackendJavaScript/JSScriptContext.h"
#include "BackendJavaScript/JSPropVisitor.h"


using namespace v8;
using namespace reflectionzeug;
namespace scriptzeug
{


static Variant wrapValue(Local<Value> arg)
{
    // Int
    if (arg->IsInt32()) {
        int value = arg->Int32Value();
        return Variant(value);
    }

    // UInt
    else if (arg->IsUint32()) {
        unsigned int value = arg->Uint32Value();
        return Variant(value);
    }

    // Double
    else if (arg->IsNumber()) {
        double value = arg->NumberValue();
        return Variant(value);
    }

    // Bool
    else if (arg->IsBoolean()) {
        bool value = arg->BooleanValue();
        return Variant(value);
    }

    // String argument
    else if (arg->IsString()) {
        String::Utf8Value str(arg);
        return Variant(std::string(*str));
    }

    // Array
    else if (arg->IsArray()) {
        Variant value(Variant::TypeArray);
        Handle<Array> arr = Handle<Array>::Cast(arg);
        for (unsigned int i=0; i<arr->Length(); i++) {
            Local<Value> prop = arr->Get(i);
            value.set(i, wrapValue(prop));
        }
        return value;
    }

    // Object
    else if (arg->IsObject()) {
        Variant value(Variant::TypeObject);
        Local<v8::Object> obj = arg->ToObject();
        Local<Array> props = obj->GetPropertyNames();
        for (unsigned int i=0; i<props->Length(); i++) {
            Local<Value> name = props->Get(i);
            String::Utf8Value ascii(name);
            std::string propName(*ascii);
            Local<Value> prop = obj->Get(name);
            value.set(propName, wrapValue(prop));
        }
        return value;
    }

    // Undefined
    return Variant();
}

static Local<Value> wrapValue(Isolate *isolate, const Variant &arg)
{
    Local<Value> value;

    if (arg.type() == Variant::TypeInt) {
        Local<Integer> v = Integer::New(isolate, arg.toInt());
        value = v;
    }

    else if (arg.type() == Variant::TypeUInt) {
        Local<Integer> v = Integer::NewFromUnsigned(isolate, arg.toUInt());
        value = v;
    }

    else if (arg.type() == Variant::TypeDouble) {
        Local<Number> v = Number::New(isolate, arg.toDouble());
        value = v;
    }

    else if (arg.type() == Variant::TypeBool) {
        Local<Boolean> v = Boolean::New(isolate, arg.toBool());
        value = v;
    }

    else if (arg.type() == Variant::TypeString) {
        Handle<String> str = String::NewFromUtf8(isolate, arg.toString().c_str());
        value = str;
    }

    else if (arg.type() == Variant::TypeArray) {
        Handle<Array> arr = Array::New(isolate, arg.size());
        for (unsigned int i=0; i<arg.size(); i++) {
            arr->Set(i, wrapValue(isolate, arg.get(i)));
        }
        value = arr;
    }

    else if (arg.type() == Variant::TypeObject) {
        Handle<v8::Object> obj = v8::Object::New(isolate);
        std::vector<std::string> args = arg.keys();
        for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {
            std::string name = *it;
            Handle<String> n = String::NewFromUtf8(isolate, name.c_str());
            obj->Set(n, wrapValue(isolate, arg.get(name)));
        }
        value = obj;
    }

    return value;
}

static void wrapFunction(const v8::FunctionCallbackInfo<Value> & args)
{
    Isolate *isolate = Isolate::GetCurrent();

    // Get function pointer
    Handle<External> data = Handle<External>::Cast(args.Data());
    AbstractFunction * func = static_cast<AbstractFunction *>(data->Value());

    // Convert arguments to a list of reflectionzeug variants
    std::vector<Variant> arguments;
    for (int i=0; i<args.Length(); i++) {
        HandleScope scope(isolate);
        Local<Value> arg = args[i];
        arguments.push_back(wrapValue(arg));
    }

    // Call the function
    Variant value = func->call(arguments);
    args.GetReturnValue().Set( wrapValue(isolate, value) );
}

static void getProperty(Local<String> property, const PropertyCallbackInfo<Value> & info)
{
    Isolate *isolate = Isolate::GetCurrent();

    // Get object
    Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    reflectionzeug::Object * obj = static_cast<reflectionzeug::Object *>(wrap->Value());
    if (obj) {
        // Get property name
        String::Utf8Value str(property);
        std::string name(*str);

        // Get property
        AbstractProperty * property = obj->property(name);
        if (property) {
            ValueProperty * vp = property->asValue();
            if (vp) {
                // Convert property value into Variant
                JSPropVisitor visitor(JSPropVisitor::GetOperation);
                vp->accept(visitor);

                // [TODO]
                info.GetReturnValue().Set(wrapValue(isolate, visitor.value()));
            }
        }
    }
}

static void setProperty(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void> & info)
{
    // Get object
    Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    reflectionzeug::Object * obj = static_cast<reflectionzeug::Object *>(wrap->Value());
    if (obj) {
        // Get property name
        String::Utf8Value str(property);
        std::string name(*str);

        // Get property
        AbstractProperty * property = obj->property(name);
        if (property) {
            ValueProperty * vp = property->asValue();
            if (vp) {
                // Set property value
                JSPropVisitor visitor(JSPropVisitor::SetOperation);
                visitor.setValue(wrapValue(value));
                vp->accept(visitor);
            }
        }
    }
}


JSScriptContext::JSScriptContext()
: m_isolate(nullptr)
{
    // Create isolate for this context
    m_isolate = Isolate::New();
    m_isolate->Enter();

    // Enter scope
    Locker locker(m_isolate);
    HandleScope scope(m_isolate);

    // Create global object
    Handle<ObjectTemplate> global = ObjectTemplate::New();

    // Create global context
    Handle<Context> context = Context::New(m_isolate, nullptr, global);
    m_context.Reset(m_isolate, context);
}

JSScriptContext::~JSScriptContext()
{
    // Destroy global context
    m_context.Reset();
    m_isolate->Exit();
    m_isolate->Dispose();

}

void JSScriptContext::registerObject(PropertyGroup * obj)
{
    // Enter scope
    Locker locker(m_isolate);
    HandleScope scope(m_isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(m_isolate, m_context);
    Context::Scope context_scope(context);

    // Get global object
    Handle<v8::Object> global = context->Global();
    registerObj(global, obj);
}

Variant JSScriptContext::evaluate(const std::string & code)
{
    // Enter scope
    Locker locker(m_isolate);
    HandleScope scope(m_isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(m_isolate, m_context);
    Context::Scope context_scope(context);

    // Create and compile script
    Handle<String> source = String::NewFromUtf8(m_isolate, code.c_str());
    Handle<Script> script = Script::Compile(source);

    // Run script
    Handle<Value> result = script->Run();
    return wrapValue(result);
}

void JSScriptContext::registerObj(Handle<v8::Object> parent, PropertyGroup * obj)
{
    // Create object template
    Handle<ObjectTemplate> templ = ObjectTemplate::New();
    templ->SetInternalFieldCount(1);

    // Register object properties
    for (unsigned int i=0; i<obj->propertyCount(); i++) {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string name = prop->name();
        if (!prop->isGroup()) {
            // Add accessor for property
            Local<String> str = String::NewFromUtf8(m_isolate, name.c_str());
            templ->SetAccessor(str, getProperty, setProperty);
        }
    }

    // Register object functions
    reflectionzeug::Object * scriptable = dynamic_cast<reflectionzeug::Object *>(obj);
    if (scriptable) {
        const std::vector<AbstractFunction *> & funcs = scriptable->functions();
        for (std::vector<AbstractFunction *>::const_iterator it = funcs.begin(); it != funcs.end(); ++it) {
            AbstractFunction * func = *it;

            // Bind pointer to AbstractFunction as an external data object
            // and set it in the function template
            Handle<External> func_ptr = External::New(m_isolate, func);
            Handle<FunctionTemplate> funcTempl =
                FunctionTemplate::New(m_isolate, wrapFunction, func_ptr);

            // Register function at object template
            Handle<v8::Function> funcObj = funcTempl->GetFunction();
            templ->Set(String::NewFromUtf8(m_isolate, func->name().c_str()), funcObj);
        }
    }

    // Make persistent template handle
    Persistent<ObjectTemplate> class_template;
    class_template.Reset(m_isolate, templ);

    // Create new object
    Handle<v8::Object> object  = templ->NewInstance();
    Handle<External>   obj_ptr = External::New(m_isolate, obj);
    object->SetInternalField(0, obj_ptr);

    // Register sub-objects
    for (unsigned int i=0; i<obj->propertyCount(); i++) {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string name = prop->name();
        if (prop->isGroup()) {
            // Add sub object
            reflectionzeug::Object * subobj = dynamic_cast<reflectionzeug::Object *>(prop);
            registerObj(object, subobj);
        }
    }

    // Register object at parent
    parent->Set(String::NewFromUtf8(m_isolate, obj->name().c_str()), object, ReadOnly);
}


} // namespace scriptzeug
