#include <functional>
#include <scriptzeug/Scriptable.h>
#include <scriptzeug/BackendJavaScript/JSScriptEnvironment.h>


namespace scriptzeug
{


using namespace v8;


static void wrapFunction(const v8::FunctionCallbackInfo<v8::Value> & args)
{
    // Get function pointer
    Handle<External> data = Handle<External>::Cast(args.Data());
    AbstractFunction * func = static_cast<AbstractFunction *>(data->Value());

    // Convert arguments to a list of scriptzeug::Variant
    std::vector<Variant> arguments;
    for (int i=0; i<args.Length(); i++) {
        v8::HandleScope scope(args.GetIsolate());

        // Int
        if (args[i]->IsInt32()) {
            int value = args[i]->Int32Value();
            arguments.push_back(Variant(value));
        }

        // Float
        else if (args[i]->IsNumber()) {
            float value = args[i]->NumberValue();
            arguments.push_back(Variant(value));
        }

        // String argument
        else if (args[i]->IsString()) {
            v8::String::AsciiValue str(args[i]);
            arguments.push_back(Variant(std::string(*str)));
        }

        // Undefined
        else {
            arguments.push_back(Variant());
        }
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

void JSScriptEnvironment::evaluate(const std::string & code)
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
    Handle<Value> result = script->Run();

    // Print result
    String::AsciiValue ascii(result);
    printf("%s\n", *ascii);
}


} // namespace
