#include <functional>
#include <reflectionzeug/Object.h>
#include <reflectionzeug/Variant.h>
#include <reflectionzeug/Function.h>
#include "scriptzeug/ScriptContext.h"
#include "BackendDuktape/DuktapeScriptContext.h"


using namespace reflectionzeug;
namespace scriptzeug
{

DuktapeScriptContext::DuktapeScriptContext(ScriptContext * scriptContext)
: AbstractScriptContext(scriptContext)
{
    m_context = duk_create_heap_default();
}

DuktapeScriptContext::~DuktapeScriptContext()
{
    duk_destroy_heap(m_context);
}

void DuktapeScriptContext::registerObject(PropertyGroup * obj)
{
}

Variant DuktapeScriptContext::evaluate(const std::string & code)
{

    return Variant();
}

} // namespace scriptzeug
