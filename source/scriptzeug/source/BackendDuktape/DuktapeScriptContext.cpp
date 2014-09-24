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
    duk_eval_string(m_context, code.c_str());

    Variant value = popDuktapeValue();

    return value;
}

Variant DuktapeScriptContext::popDuktapeValue()
{
    Variant value;
    duk_int_t type = duk_get_type(m_context, -1);

    switch(type)
    {
        case DUK_TYPE_BOOLEAN:
            value = Variant(duk_get_boolean(m_context, -1));
            break;
        case DUK_TYPE_NUMBER:
            value = Variant(duk_get_number(m_context, -1));
            break;
        case DUK_TYPE_STRING:
            value = Variant(duk_get_string(m_context, -1));
            break;
        default:
            value = Variant();
            break;
    }

    duk_pop(m_context);
    return value;
}

} // namespace scriptzeug
