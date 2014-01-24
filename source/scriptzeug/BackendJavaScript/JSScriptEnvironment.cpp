#include <functional>
#include "scriptzeug/Scriptable.h"
#include "scriptzeug/BackendJavaScript/JSScriptEnvironment.h"
#include "BackendJavaScript/JSPropVisitor.h"


namespace scriptzeug
{


using namespace v8;
using namespace zeug;


static scriptzeug::Value wrapValue(v8::Local<v8::Value> arg)
{
    // Int
    if (arg->IsInt32()) {
        int value = arg->Int32Value();
        return scriptzeug::Value(value);
    }

    // UInt
    else if (arg->IsUint32()) {
        unsigned int value = arg->Uint32Value();
        return scriptzeug::Value(value);
    }

    // Double
    else if (arg->IsNumber()) {
        double value = arg->NumberValue();
        return scriptzeug::Value(value);
    }

    // Bool
    else if (arg->IsBoolean()) {
        bool value = arg->BooleanValue();
        return scriptzeug::Value(value);
    }

    // String argument
    else if (arg->IsString()) {
        v8::String::Utf8Value str(arg);
        return scriptzeug::Value(std::string(*str));
    }

    // Array
    else if (arg->IsArray()) {
        scriptzeug::Value value(scriptzeug::Value::TypeArray);
        v8::Handle<v8::Array> arr = v8::Handle<v8::Array>::Cast(arg);
        for (int i=0; i<arr->Length(); i++) {
            v8::Local<v8::Value> prop = arr->Get(i);
            value.set(i, wrapValue(prop));
        }
        return value;
    }

    // Object
    else if (arg->IsObject()) {
        scriptzeug::Value value(scriptzeug::Value::TypeObject);
        v8::Local<v8::Object>  obj = arg->ToObject();
        v8::Local<v8::Array> props = obj->GetPropertyNames();
        for (int i=0; i<props->Length(); i++) {
            v8::Local<v8::Value> name = props->Get(i);
            v8::String::Utf8Value ascii(name);
            std::string propName(*ascii);
            v8::Local<v8::Value> prop = obj->Get(name);
            value.set(propName, wrapValue(prop));
        }
        return value;
    }

    // Undefined
    return scriptzeug::Value();
}

static v8::Local<v8::Value> wrapValue(const scriptzeug::Value &arg)
{
    v8::Isolate * isolate = Isolate::GetCurrent(); 

    v8::Local<v8::Value> value;

    if (arg.type() == scriptzeug::Value::TypeInt) {
        v8::Local<v8::Integer> v = v8::Integer::New(isolate, arg.toInt());
        value = v;
    }

    else if (arg.type() == scriptzeug::Value::TypeUInt) {
        v8::Local<v8::Integer> v = v8::Integer::NewFromUnsigned(isolate, arg.toUInt());
        value = v;
    }

    else if (arg.type() == scriptzeug::Value::TypeDouble) {
        v8::Local<v8::Number> v = v8::Number::New(isolate, arg.toDouble());
        value = v;
    }

    else if (arg.type() == scriptzeug::Value::TypeBool) {
        v8::Local<v8::Boolean> v = v8::Boolean::New(isolate, arg.toBool());
        value = v;
    }

    else if (arg.type() == scriptzeug::Value::TypeString) {
        v8::Handle<v8::String> str = String::NewFromUtf8(isolate, arg.toString().c_str());
        value = str;
    }

    else if (arg.type() == scriptzeug::Value::TypeArray) {
        v8::Handle<v8::Array> arr = Array::New(isolate, arg.size());
        for (int i=0; i<arg.size(); i++) {
            arr->Set(i, wrapValue(arg.get(i)));
        }
        value = arr;
    }

    else if (arg.type() == scriptzeug::Value::TypeObject) {
        v8::Handle<v8::Object> obj = Object::New(isolate);
        std::vector<std::string> args = arg.keys();
        for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {
            std::string name = *it;
            v8::Handle<v8::String> n = String::NewFromUtf8(isolate, name.c_str());
            obj->Set(n, wrapValue(arg.get(name)));
        }
        value = obj;
    }

    return value;
}

static void wrapFunction(const v8::FunctionCallbackInfo<v8::Value> & args)
{
    // Get function pointer
    Handle<External> data = Handle<External>::Cast(args.Data());
    AbstractFunction * func = static_cast<AbstractFunction *>(data->Value());

    // Convert arguments to a list of scriptzeug variants
    std::vector<scriptzeug::Value> arguments;
    for (int i=0; i<args.Length(); i++) {
        v8::HandleScope scope(Isolate::GetCurrent());
        v8::Local<v8::Value> arg = args[i];
        arguments.push_back(wrapValue(arg));
    }

    // Call the function
    scriptzeug::Value value = func->call(arguments);
    args.GetReturnValue().Set( wrapValue(value) );
}

static void getProperty(Local<String> property, const PropertyCallbackInfo<v8::Value> & info)
{
    // Get object
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    Scriptable * obj = static_cast<Scriptable*>(wrap->Value());
    if (obj) {
        // Get property name
        v8::String::Utf8Value str(property);
        std::string name(*str);

        // Get property
        AbstractProperty * property = obj->obtainProperty(name);
        if (property) {
            ValueProperty * vp = property->asValue();
            if (vp) {
                // Convert property value into scriptzeug::Value
                JSPropVisitor visitor(JSPropVisitor::GetOperation);
                vp->accept(visitor);

                // [TODO]
                info.GetReturnValue().Set(wrapValue(visitor.value()));
            }
        }
    }
}

static void setProperty(Local<String> property, Local<v8::Value> value, const PropertyCallbackInfo<void> & info)
{
    // Get object
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    Scriptable * obj = static_cast<Scriptable*>(wrap->Value());
    if (obj) {
        // Get property name
        v8::String::Utf8Value str(property);
        std::string name(*str);

        // Get property
        AbstractProperty * property = obj->obtainProperty(name);
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


JSScriptEnvironment::JSScriptEnvironment()
: m_isolate(nullptr)
{
    // Get isolate
    m_isolate = Isolate::GetCurrent();
    HandleScope scope(m_isolate);

    // Create global object
    Handle<ObjectTemplate> global = ObjectTemplate::New();

    // Create global context
    Handle<Context> context = Context::New(m_isolate, nullptr, global);
    m_context.Reset(m_isolate, context);
}

JSScriptEnvironment::~JSScriptEnvironment()
{
    // Destroy global context
    m_context.Reset();
}

void JSScriptEnvironment::registerObject(const std::string & name, Scriptable * obj)
{
    // Get isolate
    HandleScope scope(m_isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(m_isolate, m_context);
    Context::Scope context_scope(context);

    // Create class template
    Handle<ObjectTemplate> templ = ObjectTemplate::New();
    templ->SetInternalFieldCount(1);

    // Register object properties
    for (unsigned int i=0; i<obj->propertyCount(); i++) {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string name = prop->name();

        // Add accessor for property
        Local<v8::String> str = String::NewFromUtf8(m_isolate, name.c_str());
        templ->SetAccessor(str, getProperty, setProperty);
    }

    // Register object functions
    const std::vector<AbstractFunction *> & funcs = obj->functions();
    for (std::vector<AbstractFunction *>::const_iterator it = funcs.begin(); it != funcs.end(); ++it) {
        AbstractFunction * func = *it;

        // Bind pointer to AbstractFunction as an external data object
        // and set it in the function template
        Handle<External> func_ptr = External::New(m_isolate, func);
        v8::Handle<v8::FunctionTemplate> funcTempl =
            FunctionTemplate::New(m_isolate, wrapFunction, func_ptr);

        // Register function at object template
        v8::Handle<v8::Function> funcObj = funcTempl->GetFunction();
        templ->Set(String::NewFromUtf8(m_isolate, func->name().c_str()), funcObj);
    }

    // Make persistent template handle
    Persistent<ObjectTemplate> class_template;
    class_template.Reset(m_isolate, templ);

    // Create new object
    Handle<Object>   object  = templ->NewInstance();
    Handle<External> obj_ptr = External::New(m_isolate, obj);
    object->SetInternalField(0, obj_ptr);

    // Register object in global variables
    context->Global()->Set(String::NewFromUtf8(m_isolate, name.c_str()), object, ReadOnly);
}

scriptzeug::Value JSScriptEnvironment::evaluate(const std::string & code)
{
    HandleScope scope(m_isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(m_isolate, m_context);
    Context::Scope context_scope(context);

    // Create and compile script
    Handle<String> source = String::NewFromUtf8(m_isolate, code.c_str());
    Handle<Script> script = Script::Compile(source);

    // Run script
    Handle<v8::Value> result = script->Run();
    return wrapValue(result);
}


} // namespace
