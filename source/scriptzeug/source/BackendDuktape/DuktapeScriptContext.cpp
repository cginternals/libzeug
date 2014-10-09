#include <functional>
#include <reflectionzeug/Object.h>
#include <reflectionzeug/Variant.h>
#include <reflectionzeug/Function.h>
#include "scriptzeug/ScriptContext.h"
#include "BackendDuktape/DuktapeScriptContext.h"


using namespace reflectionzeug;
namespace scriptzeug
{


static Variant fromDukValue(duk_context * context, duk_idx_t index = -1)
{
    Variant value;
    duk_int_t type = duk_get_type(context, index);

    switch(type)
    {
        case DUK_TYPE_BOOLEAN:
            value = Variant(duk_get_boolean(context, index));
            break;
        case DUK_TYPE_NUMBER:
            value = Variant(duk_get_number(context, index));
            break;
        case DUK_TYPE_STRING:
            value = Variant(duk_get_string(context, index));
            break;
        default:
            value = Variant();
            break;
    }

    return value;
}


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
    duk_int_t error = duk_peval_string(m_context, code.c_str());

    if (error)
    {
        m_scriptContext->scriptException(std::string(duk_safe_to_string(m_context, -1)));
        return Variant();
    }

    Variant value = fromDukValue(m_context);
    duk_pop(m_context);

    return value;
}


} // namespace scriptzeug
