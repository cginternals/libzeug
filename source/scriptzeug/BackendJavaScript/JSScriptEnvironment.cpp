#include <iostream>
#include <functional>
#include "scriptzeug/Scriptable.h"
#include "scriptzeug/BackendJavaScript/JSScriptEnvironment.h"


namespace scriptzeug
{


using namespace v8;


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
        v8::String::AsciiValue str(arg);
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
            v8::String::AsciiValue ascii(name);
            std::string propName(*ascii);
            v8::Local<v8::Value> prop = obj->Get(name);
            value.set(propName, wrapValue(prop));
        }
        return value;
    }

    // Undefined
    return scriptzeug::Value();
}

static void wrapFunction(const v8::FunctionCallbackInfo<v8::Value> & args)
{
    // Get function pointer
    Handle<External> data = Handle<External>::Cast(args.Data());
    AbstractFunction * func = static_cast<AbstractFunction *>(data->Value());

    // Convert arguments to a list of scriptzeug variants
    std::vector<scriptzeug::Value> arguments;
    for (int i=0; i<args.Length(); i++) {
        v8::HandleScope scope(args.GetIsolate());
        v8::Local<v8::Value> arg = args[i];
        arguments.push_back(wrapValue(arg));
    }

    // Call the function
    func->call(arguments);

    // Set return value
    /*
    v8::Handle<v8::String> source = ReadFile(args.GetIsolate(), *file);
    args.GetReturnValue().Set(source);
    */
}


JSScriptEnvironment::JSScriptEnvironment()
{
    // Get isolate
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Create global object
    Handle<ObjectTemplate> global = ObjectTemplate::New();

    // Create global context
    Handle<Context> context = Context::New(isolate, nullptr, global);
    m_context.Reset(isolate, context);
}

JSScriptEnvironment::~JSScriptEnvironment()
{
    // Destroy global context
    m_context.Dispose();
}

void JSScriptEnvironment::registerObject(const std::string & name, Scriptable * obj)
{
    // Get isolate
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(isolate, m_context);
    Context::Scope context_scope(context);

    // Create class template
    Handle<ObjectTemplate> templ = ObjectTemplate::New();
    templ->SetInternalFieldCount(1);

    // Register object functions
    const std::vector<AbstractFunction *> & funcs = obj->functions();
    for (std::vector<AbstractFunction *>::const_iterator it = funcs.begin(); it != funcs.end(); ++it) {
        AbstractFunction * func = *it;

        // Bind pointer to AbstractFunction as an external data object
        // and set it in the function template
        Handle<External> func_ptr = External::New(func);
        v8::Handle<v8::FunctionTemplate> funcTempl =
            FunctionTemplate::New(wrapFunction, func_ptr);

        // Register function at object template
        v8::Handle<v8::Function> funcObj = funcTempl->GetFunction();
        templ->Set(String::New(func->name().c_str()), funcObj);
    }

    // Make persistent template handle
    Persistent<ObjectTemplate> class_template;
    class_template.Reset(isolate, templ);

    // Create new object
    Handle<Object>   object  = templ->NewInstance();
    Handle<External> obj_ptr = External::New(obj);
    object->SetInternalField(0, obj_ptr);

    // Register object in global variables
    context->Global()->Set(String::New(name.c_str()), object, ReadOnly);
}

scriptzeug::Value JSScriptEnvironment::evaluate(const std::string & code)
{
    // Get isolate
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(isolate, m_context);
    Context::Scope context_scope(context);

    // Create and compile script
    Handle<String> source = String::New(code.c_str());
    Handle<Script> script = Script::Compile(source);

    // Run script
    Handle<v8::Value> result = script->Run();
    return wrapValue(result);
}


} // namespace
