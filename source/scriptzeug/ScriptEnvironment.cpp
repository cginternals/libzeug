#include <scriptzeug/ScriptEnvironment.h>
#include <scriptzeug/Backend/AbstractScriptEnvironment.h>
#ifdef LIBZEUG_USE_V8
    #include <scriptzeug/BackendJavaScript/JSScriptEnvironment.h>
#endif

namespace scriptzeug
{


ScriptEnvironment::ScriptEnvironment(const std::string & backend)
: m_backend(nullptr)
{
    // Create backend
#ifdef LIBZEUG_USE_V8
    if (backend == "javascript")
        m_backend = new JSScriptEnvironment();
#endif
}

ScriptEnvironment::~ScriptEnvironment()
{
    // Release backend
    if (m_backend)
        delete m_backend;
}

void ScriptEnvironment::registerObject(const std::string & name, Scriptable * obj)
{
    if (m_backend)
        m_backend->registerObject(name, obj);
}

void ScriptEnvironment::evaluate(const std::string & code)
{
    if (m_backend)
        m_backend->evaluate(code);
}


} // namespace
