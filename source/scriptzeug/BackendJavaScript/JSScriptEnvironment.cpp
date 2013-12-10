#include <functional>
#include <scriptzeug/BackendJavaScript/JSScriptEnvironment.h>


namespace scriptzeug
{


using namespace v8;


template <typename... Arguments>
class ArgParser
{
public:
    ArgParser() {
    }

    ~ArgParser() {
    }

    void parse(const v8::FunctionCallbackInfo<v8::Value> & args, int index = 0) {
    }
};

template<typename... Arguments>
class ArgParser<int, Arguments...> : public ArgParser<Arguments...>
{
public:
    ArgParser() {
    }

    ~ArgParser() {
    }

    void parse(const v8::FunctionCallbackInfo<v8::Value> & args, int index = 0) {
        if (index < args.Length()) {
            printf("int: %d\n", args[index]->Int32Value());
        }

        ArgParser<Arguments...>::parse(args, index+1);
    }
};

template<typename... Arguments>
class ArgParser<float, Arguments...> : public ArgParser<Arguments...>
{
public:
    ArgParser() {
    }

    ~ArgParser() {
    }

    void parse(const v8::FunctionCallbackInfo<v8::Value> & args, int index = 0) {
        if (index < args.Length()) {
            printf("float: %.4f\n", args[index]->NumberValue());
        }

        ArgParser<Arguments...>::parse(args, index+1);
    }
};

template<typename... Arguments>
class ScriptFunc
{
public:
    typedef std::function<void(Arguments...)> Function;

    ArgParser<Arguments...> argParser;
};


static void testFunction(const v8::FunctionCallbackInfo<v8::Value> & args)
{
    //printf("Hello World!\n");

    /*
    for (int i=0; i<args.Length(); i++) {
        v8::HandleScope scope(args.GetIsolate());

        // String argument
//      v8::String::AsciiValue str(args[i]);
//      printf("%s\n", *str);

        // Int argument
        int num = args[i]->Int32Value();
        printf("%d\n", num);
    }
    */

    // Set return value
    /*
    v8::Handle<v8::String> source = ReadFile(args.GetIsolate(), *file);
    args.GetReturnValue().Set(source);
    */

    ArgParser<int, float, float, float> argParser;
    argParser.parse(args);
}


JSScriptEnvironment::JSScriptEnvironment()
{
	// Get isolate
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // Create global object
    Handle<ObjectTemplate> global = ObjectTemplate::New();
    global->Set(String::New("test"), FunctionTemplate::New(testFunction));

	// Create global context
    Handle<Context> context = Context::New(isolate, nullptr, global);
    m_context.Reset(isolate, context);
}

JSScriptEnvironment::~JSScriptEnvironment()
{
	// Destroy global context
    m_context.Dispose();
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
