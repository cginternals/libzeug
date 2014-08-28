#include <scriptzeug/ScriptContext.h>
#include <scriptzeug/Backend/AbstractScriptContext.h>
#ifdef LIBZEUG_USE_V8
    #include "BackendJavaScript/JSScriptContext.h"
#endif


using namespace reflectionzeug;
namespace scriptzeug
{


ScriptContext::ScriptContext(const std::string & backend)
: m_backend(nullptr)
{
    // Create backend
#ifdef LIBZEUG_USE_V8
    if (backend == "javascript")
        m_backend = new JSScriptContext(this);
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
