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

static void pushToDukStack(duk_context * context, Variant & var)
{
    if (var.hasType<char*>()) {
        duk_push_string(context, var.value<char*>());
    }

    else if (var.hasType<std::string>()) {
        duk_push_string(context, var.value<std::string>().c_str());
    }

    else if (var.hasType<float>()) {
        duk_push_number(context, var.value<float>());
    }

    else if (var.hasType<double>()) {
        duk_push_number(context, var.value<double>());
    }

    else if (var.hasType<int>()) {
        duk_push_int(context, var.value<int>());
    }

    else if (var.hasType<bool>()) {
        duk_push_boolean(context, var.value<bool>());
    }

    else if (var.canConvert<double>()) {
        duk_push_number(context, var.value<double>());
    }

    else if (var.canConvert<std::string>()) {
        duk_push_string(context, var.value<std::string>().c_str());
    }

    else {
        std::cout << var.isMap() << " " << std::endl;
    }
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

        if (!value.isNull())
        {
            pushToDukStack(context, value);
            return 1;
        } else {
            return 0;
        }
    } else {
        std::cerr << "Error: No valid pointer found." << std::endl;
        return DUK_RET_ERROR;
    }

    return 0;   /*  1 = return value at top
                 *  0 = return 'undefined'
                 * <0 = throw error (use DUK_RET_xxx constants)
                 */
}

static Variant getPropertyValue(AbstractProperty * property)
{
    // Get property value
    Variant value;

    // Boolean
    if (Property<bool> * prop = dynamic_cast< Property<bool> * >(property) ) {
        value = Variant(prop->value());
    }

    // Unsigned integral
    else if (UnsignedIntegralPropertyInterface * prop = dynamic_cast< UnsignedIntegralPropertyInterface * >(property) ) {
        value = Variant((unsigned int)prop->toULongLong());
    }

    // Signed integral
    else if (SignedIntegralPropertyInterface * prop = dynamic_cast< SignedIntegralPropertyInterface * >(property) ) {
        value = Variant((int)prop->toLongLong());
    }

    // Floating point number
    else if (FloatingPointPropertyInterface * prop = dynamic_cast< FloatingPointPropertyInterface * >(property) ) {
        value = Variant((double)prop->toDouble());
    }

    // Enum
    else if (EnumPropertyInterface * prop = dynamic_cast< EnumPropertyInterface * >(property) ) {
        value = Variant(prop->toString());
    }

    // String
    else if (StringPropertyInterface * prop = dynamic_cast< StringPropertyInterface * >(property) ) {
        value = Variant(prop->toString());
    }

    // FilePath
    else if (Property<FilePath> * prop = dynamic_cast< Property<FilePath> * >(property) ) {
        value = Variant(prop->value().toString());
    }

    // Color
    else if (ColorPropertyInterface * prop = dynamic_cast< ColorPropertyInterface * >(property) ) {
        value = Variant(prop->toColor().toString());
    }

    // Array
    else if (AbstractPropertyCollection * prop = dynamic_cast< AbstractPropertyCollection * >(property) ) {
        VariantArray array;
        for (size_t i=0; i<prop->count(); i++) {
            AbstractProperty * subprop = prop->at(i);
            array.push_back(getPropertyValue(subprop));
        }
        value = Variant(array);
    }

    // Return value
    return value;
}

static void setPropertyValue(AbstractProperty * property, const Variant &value)
{
    // Check property
    if (property) {
         // Boolean
        if (Property<bool> * prop = dynamic_cast< Property<bool> * >(property) ) {
            prop->setValue( value.value<bool>() );
        }

        // Unsigned integral
        else if (UnsignedIntegralPropertyInterface * prop = dynamic_cast< UnsignedIntegralPropertyInterface * >(property) ) {
            prop->fromULongLong( value.value<unsigned int>() );
        }

        // Signed integral
        else if (SignedIntegralPropertyInterface * prop = dynamic_cast< SignedIntegralPropertyInterface * >(property) ) {
            prop->fromLongLong( value.value<int>() );
        }

        // Floating point number
        else if (FloatingPointPropertyInterface * prop = dynamic_cast< FloatingPointPropertyInterface * >(property) ) {
            prop->fromDouble( value.value<double>() );
        }

        // Enum
        else if (EnumPropertyInterface * prop = dynamic_cast< EnumPropertyInterface * >(property) ) {
            prop->fromString( value.value<std::string>() );
        }

        // String
        else if (StringPropertyInterface * prop = dynamic_cast< StringPropertyInterface * >(property) ) {
            prop->fromString( value.value<std::string>() );
        }

        // FilePath
        else if (Property<FilePath> * prop = dynamic_cast< Property<FilePath> * >(property) ) {
            prop->setValue( value.value<std::string>() );
        }

        // Color
        else if (ColorPropertyInterface * prop = dynamic_cast< ColorPropertyInterface * >(property) ) {
            if (value.hasType<VariantArray>()) {
                VariantArray array = value.value<VariantArray>();
                Color color(0, 0, 0, 255);
                switch (array.size()) 
                {
                case 4: 
                    color.setAlpha(array.at(3).value<int>());
                case 3:
                    color.setBlue(array.at(2).value<int>());
                    color.setGreen(array.at(1).value<int>());
                    color.setRed(array.at(0).value<int>());
                }
                prop->fromColor(color);
            } else if (value.hasType<VariantMap>()) {
                VariantMap map = value.value<VariantMap>();
                int r = map.count("r") >= 1 ? map.at("r").value<int>() : 0;
                int g = map.count("g") >= 1 ? map.at("g").value<int>() : 0;
                int b = map.count("b") >= 1 ? map.at("b").value<int>() : 0;
                int a = map.count("a") >= 1 ? map.at("a").value<int>() : 255;
                prop->fromColor(Color(r, g, b, a));
            } else {
                prop->fromString(value.value<std::string>());
            }
        }

        // Array
        else if (AbstractPropertyCollection * prop = dynamic_cast< AbstractPropertyCollection * >(property) ) {
            if (value.hasType<VariantArray>()) {
                VariantArray array = value.value<VariantArray>();
                for (size_t i=0; i<(size_t)array.size() && i<prop->count(); i++) {
                    AbstractProperty * subprop = prop->at(i);
                    setPropertyValue(subprop, array.at(i));
                }
            }
        }
    }
}

static duk_ret_t getProperty(duk_context * context)
{
    // Get object
    duk_push_this(context);
    duk_get_prop_string(context, -1, "object_pointer");
    void * ptr = duk_get_pointer(context, -1);
    duk_pop(context);
    duk_pop(context);
    reflectionzeug::Object * obj = static_cast<reflectionzeug::Object *>(ptr);

    if (obj) {
        // Get property
        duk_push_current_function(context);
        duk_get_prop_string(context, -1, "property_name");
        std::string propName = duk_get_string(context, -1);
        duk_pop(context);
        duk_pop(context);
        AbstractProperty * property = obj->property(propName);

        if (property) {
            // Get property value
            Variant value = getPropertyValue(property);

            // Set return value
            pushToDukStack(context, value);
        }
    }

    return 1;   /*  1 = return value at top
                 *  0 = return 'undefined'
                 * <0 = throw error (use DUK_RET_xxx constants)
                 */
}

static duk_ret_t setProperty(duk_context * context)
{
    // Get value from stack
    Variant value = fromDukValue(context, -1);
    duk_pop(context);

    // Get object
    duk_push_this(context);
    duk_get_prop_string(context, -1, "object_pointer");
    void * ptr = duk_get_pointer(context, -1);
    duk_pop(context);
    duk_pop(context);
    reflectionzeug::Object * obj = static_cast<reflectionzeug::Object *>(ptr);

    if (obj) {
        // Get property
        duk_push_current_function(context);
        duk_get_prop_string(context, -1, "property_name");
        std::string propName = duk_get_string(context, -1);
        duk_pop(context);
        duk_pop(context);
        AbstractProperty * property = obj->property(propName);

        if (property) {
            // Set property value
            setPropertyValue(property, value);
        }
    }

    return 0;   /*  1 = return value at top
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
        duk_pop(m_context);
        return Variant();
    }

    Variant value = fromDukValue(m_context);
    duk_pop(m_context);

    return value;
}

void DuktapeScriptContext::registerObj(duk_idx_t parentId, PropertyGroup * obj)
{
    // Helper Ecmascript function
    const std::string defineAccessor = "function defineAccessor(obj, key, set, get) {\n"
                                            "Object.defineProperty(obj, key, {\n"
                                                "enumerable: true, configurable: true,\n"
                                                "set: set, get: get\n"
                                            "});\n"
                                            "return obj;\n"
                                        "}";
    duk_eval_string_noresult(m_context, defineAccessor.c_str());

    // Create empty object on the stack
    duk_idx_t objIndex = duk_push_object(m_context);

    duk_push_pointer(m_context, static_cast<void *>(obj));
    duk_put_prop_string(m_context, -2, "object_pointer");

    // Register object properties
    for (unsigned int i=0; i<obj->count(); i++) {
        // Get property
        AbstractProperty * prop = obj->at(i);
        std::string propName = prop->name();

        // Check if property is a property group
        PropertyGroup * group = dynamic_cast< PropertyGroup * >(prop);
        if (!group) {
            duk_eval_string(m_context, "defineAccessor");
            // Obj
            duk_dup(m_context, -2);
            // Key (for accessor)
            duk_push_string(m_context, propName.c_str());
            // Setter function object
            duk_push_c_function(m_context, setProperty, 1);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, "property_name");
            // Getter function object
            duk_push_c_function(m_context, getProperty, 0);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, "property_name");

            duk_call(m_context, 4);
            duk_remove(m_context, -1);
        }
    }

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

    // Register sub-objects
    for (unsigned int i=0; i<obj->count(); i++) {
        // Get property
        AbstractProperty * prop = obj->at(i);
        std::string name = prop->name();
        if (PropertyGroup * group = dynamic_cast< PropertyGroup * >(prop)) {
            // Add sub object
            registerObj(objIndex, group);
        }
    }

    // Register object in parent object (global if it is no sub-object)
    duk_put_prop_string(m_context, parentId, obj->name().c_str());

    // // Register object properties as real accessors, e.g. obj.prop as getter and obj.prop = X as setter
    // for (unsigned int i=0; i<obj->count(); i++) {
    //     // Get property
    //     AbstractProperty * prop = obj->at(i);
    //     std::string propName = prop->name();

    //     // Check if property is a property group
    //     PropertyGroup * group = dynamic_cast< PropertyGroup * >(prop);
    //     if (!group) {
    //         std::string propertyAccessorRegistration = "Object.defineProperty(" + obj->name() + ", '" + propName + "', {\n"
    //             "enumerable: false,\n"
    //             "configurable: false,\n"
    //             "get: function () {\n"
    //                 "return this.property_" + propName + "_get();\n"
    //             "},\n"
    //             "set: function (v) {\n"
    //                 "this.property_" + propName + "_set(v);\n"
    //             "}\n"
    //         "});";

    //         std::cerr << duk_get_top(m_context) << std::endl;
    //         duk_eval_string(m_context, propertyAccessorRegistration.c_str());
    //         std::cerr << duk_get_top(m_context) << std::endl;
    //         duk_pop(m_context);
    //         std::cerr << duk_get_top(m_context) << std::endl;

    //         // evaluate(propertyAccessorRegistration);
    //     }
    // }
}


} // namespace scriptzeug
