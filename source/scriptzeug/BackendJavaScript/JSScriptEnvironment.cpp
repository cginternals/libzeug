#include <scriptzeug/BackendJavaScript/JSScriptEnvironment.h>


namespace scriptzeug
{


using namespace v8;


JSScriptEnvironment::JSScriptEnvironment()
{
	// Get isolate
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope handle_scope(isolate);

	// Create global context
    Handle<Context> context = Context::New(isolate);
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
    HandleScope handle_scope(isolate);

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
