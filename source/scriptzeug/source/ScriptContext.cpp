
#include <scriptzeug/ScriptContext.h>

#include <scriptzeug/backend/AbstractScriptContext.h>

#include "backend-duktape/DuktapeScriptContext.h"


using namespace reflectionzeug;


namespace scriptzeug
{


ScriptContext::ScriptContext(const std::string & backend)
: m_backend(nullptr)
{
    // Create backend

    // Javascript (duktape)
    if (backend == "duktape" || backend == "javascript" || backend == "js")
    {
        m_backend = new DuktapeScriptContext();
        m_backend->initialize(this);
    }
}

ScriptContext::ScriptContext(AbstractScriptContext * backend)
: m_backend(backend)
{
    // Register backend
    if (m_backend) {
        m_backend->initialize(this);
    }
}

ScriptContext::~ScriptContext()
{
    // Release backend
    delete m_backend;
}

void ScriptContext::setGlobalNamespace(const std::string & name)
{
    if (m_backend)
    {
        m_backend->setGlobalNamespace(name);
    }
}

void ScriptContext::registerObject(reflectionzeug::PropertyGroup * obj)
{
    if (m_backend)
    {
        m_backend->registerObject(obj);
    }
}

void ScriptContext::unregisterObject(reflectionzeug::PropertyGroup * obj)
{
    if (m_backend)
    {
        m_backend->unregisterObject(obj);
    }
}

Variant ScriptContext::evaluate(const std::string & code)
{
    if (m_backend)
    {
        return m_backend->evaluate(code);
    }
    else
    {
        return Variant();
    }
}


} // namespace scriptzeug
