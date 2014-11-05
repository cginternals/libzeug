#include <scriptzeug/ScriptContext.h>
#include <scriptzeug/backend/AbstractScriptContext.h>

#include "backend-duktape/DuktapeScriptContext.h"

#ifdef LIBZEUG_USE_V8
    #include "backend-v8/V8ScriptContext.h"
#endif


using namespace reflectionzeug;
namespace scriptzeug
{


ScriptContext::ScriptContext(const std::string & backend)
: m_backend(nullptr)
{
    // Create backend

    // Javascript (default: duktape)

    // Duktape
    if (backend == "duktape" || backend == "javascript" || backend == "js") {
        m_backend = new DuktapeScriptContext(this);
    }

    // V8
#ifdef LIBZEUG_USE_V8
    else if (backend == "v8") {
        m_backend = new V8ScriptContext(this);
    }
#endif
}

ScriptContext::~ScriptContext()
{
    // Release backend
    if (m_backend)
        delete m_backend;
}

void ScriptContext::registerObject(reflectionzeug::PropertyGroup * obj)
{
    if (m_backend)
        m_backend->registerObject(obj);
}

Variant ScriptContext::evaluate(const std::string & code)
{
    if (m_backend)
        return m_backend->evaluate(code);
    else
        return Variant();
}


} // namespace scriptzeug
