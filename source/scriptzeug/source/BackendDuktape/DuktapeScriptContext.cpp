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

static duk_ret_t wrapFunction(duk_context * context)
{
    duk_int_t magic = (unsigned int) duk_get_current_magic(context) & 0xffffU;

    duk_idx_t nargs = duk_get_top(context);

    duk_push_global_stash(context);
    duk_push_int(context, magic);
    duk_get_prop(context, -2);
    void * ptr = duk_get_pointer(context, -1);

    duk_pop(context);
    duk_pop(context);

    if (ptr)
    {
        AbstractFunction * func = static_cast<AbstractFunction *>(ptr);

        std::vector<Variant> arguments(nargs);
        for (int i = 0; i < nargs; ++i){
            arguments[i] = fromDukValue(context, 0);
            duk_remove(context, 0);
        }

        Variant value = func->call(arguments);
    } else {
        std::cerr << "Error: No valid pointer found." << std::endl;
        return DUK_RET_ERROR;
    }

    return 1;   /*  1 = return value at top
                 *  0 = return 'undefined'
                 * <0 = throw error (use DUK_RET_xxx constants)
                 */
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
    duk_push_global_object(m_context);

    registerObj(duk_get_top_index(m_context), obj);

    duk_pop(m_context);
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

void DuktapeScriptContext::registerObj(duk_idx_t parentId, PropertyGroup * obj)
{
    // Create empty object on the stack
    duk_idx_t objIndex = duk_push_object(m_context);

    // Register object functions
    reflectionzeug::Object * scriptable = dynamic_cast<reflectionzeug::Object *>(obj);
    if (scriptable) {
        const std::vector<AbstractFunction *> & funcs = scriptable->functions();
        for (std::vector<AbstractFunction *>::const_iterator it = funcs.begin(); it != funcs.end(); ++it) {
            AbstractFunction * func = *it;

            duk_push_global_stash(m_context);

            if (!duk_has_prop_string(m_context, -1, "currentIndex"))
            {
                duk_push_int(m_context, 0);
                duk_put_prop_string(m_context, -2, "currentIndex");
            }

            duk_get_prop_string(m_context, -1, "currentIndex");
            duk_int_t currentIndex = duk_get_int(m_context, -1);
            duk_pop(m_context);

            if (currentIndex >= 65535)
            {
                std::cerr << "Error: Limit for registering functions reached (65536)." << std::endl;
                duk_pop(m_context);
                continue;
            }

            duk_push_int(m_context, currentIndex + 1);
            duk_put_prop_string(m_context, -2, "currentIndex");

            duk_push_int(m_context, currentIndex);
            duk_push_pointer(m_context, static_cast<void *>(func));
            duk_put_prop(m_context, -3);
            duk_pop(m_context);

            duk_push_c_function(m_context, wrapFunction, DUK_VARARGS);
            duk_set_magic(m_context, -1, currentIndex);

            duk_put_prop_string(m_context, objIndex, func->name().c_str());
        }
    }

    duk_put_prop_string(m_context, parentId, obj->name().c_str());
}


} // namespace scriptzeug
