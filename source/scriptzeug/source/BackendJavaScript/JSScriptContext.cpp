#include <functional>
#include <reflectionzeug/Object.h>
#include <reflectionzeug/Variant.h>
#include <reflectionzeug/Function.h>
#include "scriptzeug/ScriptContext.h"
#include "BackendJavaScript/JSScriptContext.h"


using namespace v8;
using namespace reflectionzeug;
namespace scriptzeug
{


static Variant fromV8Value(Isolate *isolate, Local<Value> arg);
static Local<Value> toV8Value(Isolate *isolate, const Variant &arg);


class JSScriptFunction : public reflectionzeug::AbstractFunction
{
public:
    JSScriptFunction(v8::Isolate *isolate, v8::Handle<v8::Function> &func)
    : AbstractFunction("")
    , m_isolate(isolate)
    , m_func(isolate, func)
    {
    }

    virtual ~JSScriptFunction()
    {
        m_func.Reset();
    }

    virtual AbstractFunction *clone()
    {
        // Copy handle
        HandleScope scope(m_isolate);
        Local<v8::Function> func = Local<v8::Function>::New(m_isolate, m_func);

        // Create new instance
        return new JSScriptFunction(m_isolate, func);
    }

    virtual Variant call(const std::vector<Variant> & args)
    {
        Locker locker(m_isolate);
        HandleScope scope(m_isolate);

        // Get local handle to the function
        Local<v8::Function> func = Local<v8::Function>::New(m_isolate, m_func);

        // Create list of arguments for v8
        // [TODO] Support more than 32 arguments by making the array flexible
        Handle<v8::Value> v8args[32];
        int numArgs = args.size();
        if (numArgs > 32) numArgs = 32;
        if (numArgs > 0) {
            // Convert arguments from reflectionzeug-Variant to v8 value
            for (int i=0; i<numArgs; i++) {
                v8args[i] = toV8Value(m_isolate, args[i]);
            }
        }

        // Call the function (use the function-object itself as 'this')
        TryCatch trycatch;
        Handle<Value> res = func->Call(func, numArgs, v8args);
        if (res.IsEmpty()) {
            return Variant();
        } else {
            // Convert return value to VariantOld
            return fromV8Value(m_isolate, res);
        }
    }

protected:
        v8::Isolate                  *m_isolate;
        v8::Persistent<v8::Function>  m_func;
};


static Variant fromV8Value(Isolate *isolate, Local<Value> arg)
{
    // Function
    if (arg->IsFunction()) { // Remember: A function is also an object, so check for functions first
        Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(arg);
        JSScriptFunction *function = new JSScriptFunction(isolate, func);
        return Variant::fromValue<AbstractFunction *>(function);
    }

    // Int
    else if (arg->IsInt32()) {
        int value = arg->Int32Value();
        return Variant(value);
    }

    // UInt
    else if (arg->IsUint32()) {
        unsigned int value = arg->Uint32Value();
        return Variant(value);
    }

    // Double
    else if (arg->IsNumber()) {
        double value = arg->NumberValue();
        return Variant(value);
    }

    // Bool
    else if (arg->IsBoolean()) {
        bool value = arg->BooleanValue();
        return Variant(value);
    }

    // String argument
    else if (arg->IsString()) {
        String::Utf8Value str(arg);
        return Variant(std::string(*str));
    }

    // Array
    else if (arg->IsArray()) {
        VariantArray array;
        Handle<Array> arr = Handle<Array>::Cast(arg);
        for (unsigned int i=0; i<arr->Length(); i++) {
            Local<Value> prop = arr->Get(i);
            array.push_back(fromV8Value(isolate, prop));
        }
        return Variant();
    }

    // Object
    else if (arg->IsObject()) {
        VariantMap map;
        Local<v8::Object> obj = arg->ToObject();
        Local<Array> props = obj->GetPropertyNames();
        for (unsigned int i=0; i<props->Length(); i++) {
            Local<Value> name = props->Get(i);
            String::Utf8Value ascii(name);
            std::string propName(*ascii);
            Local<Value> prop = obj->Get(name);
            map.insert({ propName, fromV8Value(isolate, prop) });
        }
        return Variant(map);
    }

    // Undefined
    return Variant();
}

static Local<Value> toV8Value(Isolate *isolate, const Variant &arg)
{
    Local<Value> value;

    if (arg.hasType<int>()) {
        Local<Integer> v = Integer::New(isolate, arg.value<int>());
        value = v;
    }

    else if (arg.hasType<unsigned int>()) {
        Local<Integer> v = Integer::NewFromUnsigned(isolate, arg.value<unsigned int>());
        value = v;
    }

    else if (arg.hasType<double>()) {
        Local<Number> v = Number::New(isolate, arg.value<double>());
        value = v;
    }

    else if (arg.hasType<bool>()) {
        Local<Boolean> v = Boolean::New(isolate, arg.value<bool>());
        value = v;
    }

    else if (arg.hasType<std::string>()) {
        Handle<String> str = String::NewFromUtf8(isolate, arg.value<std::string>().c_str());
        value = str;
    }

    else if (arg.hasType<VariantArray>()) {
        VariantArray variantArray = arg.value<VariantArray>();
        Handle<Array> arr = Array::New(isolate, variantArray.size());
        for (unsigned int i=0; i<variantArray.size(); i++) {
            arr->Set(i, toV8Value(isolate, variantArray.at(i)));
        }
        value = arr;
    }

    else if (arg.hasType<VariantMap>()) {
        VariantMap variantMap = arg.value<VariantMap>();
        Handle<v8::Object> obj = v8::Object::New(isolate);
        for (const std::pair<std::string, Variant> & pair : variantMap)
        {
            Handle<String> n = String::NewFromUtf8(isolate, pair.first.c_str());
            obj->Set(n, toV8Value(isolate, pair.second));
        }
        value = obj;
    }

    return value;
}

static void wrapFunction(const v8::FunctionCallbackInfo<Value> & args)
{
    Isolate *isolate = Isolate::GetCurrent();

    // Get function pointer
    Handle<External> data = Handle<External>::Cast(args.Data());
    AbstractFunction * func = static_cast<AbstractFunction *>(data->Value());

    // Convert arguments to a list of reflectionzeug variants
    std::vector<Variant> arguments;
    for (int i=0; i<args.Length(); i++) {
        HandleScope scope(isolate);
        Local<Value> arg = args[i];
        arguments.push_back(fromV8Value(isolate, arg));
    }

    // Call the function
    Variant value = func->call(arguments);
    args.GetReturnValue().Set( toV8Value(isolate, value) );
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
                int r = array.at(0).value<int>();
                int g = array.at(1).value<int>();
                int b = array.at(2).value<int>();
                int a = array.at(3).value<int>();
                prop->fromColor(Color(r, g, b, a));
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

static void getProperty(Local<String> propertyName, const PropertyCallbackInfo<Value> & info)
{
    Isolate *isolate = Isolate::GetCurrent();

    // Get object
    Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    reflectionzeug::Object * obj = static_cast<reflectionzeug::Object *>(wrap->Value());
    if (obj) {
        // Get property
        String::Utf8Value str(propertyName);
        std::string name(*str);
        AbstractProperty * property = obj->property(name);
        if (property) {
            // Get property value
            Variant value = getPropertyValue(property);

            // Set return value
            info.GetReturnValue().Set( toV8Value(isolate, value) );
        }
    }
}

static void setProperty(Local<String> propertyName, Local<Value> value, const PropertyCallbackInfo<void> & info)
{
    Isolate *isolate = Isolate::GetCurrent();

    // Convert value into Variant
    Variant v = fromV8Value(isolate, value);

    // Get object
    Local<v8::Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    reflectionzeug::Object * obj = static_cast<reflectionzeug::Object *>(wrap->Value());
    if (obj) {
        // Get property
        String::Utf8Value str(propertyName);
        std::string name(*str);
        AbstractProperty * property = obj->property(name);
        if (property) {
            // Set property value
            setPropertyValue(property, v);
        }
    }
}


JSScriptContext::JSScriptContext(ScriptContext *scriptContext)
: AbstractScriptContext(scriptContext)
, m_isolate(nullptr)
{
    // Create isolate for this context
    m_isolate = Isolate::New();
    m_isolate->Enter();

    // Enter scope
    Locker locker(m_isolate);
    HandleScope scope(m_isolate);

    // Create global object
    Handle<ObjectTemplate> global = ObjectTemplate::New();

    // Create global context
    Handle<Context> context = Context::New(m_isolate, nullptr, global);
    m_context.Reset(m_isolate, context);
}

JSScriptContext::~JSScriptContext()
{
    // Destroy global context
    m_context.Reset();
    m_isolate->Exit();
    m_isolate->Dispose();

}

void JSScriptContext::registerObject(PropertyGroup * obj)
{
    // Enter scope
    Locker locker(m_isolate);
    HandleScope scope(m_isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(m_isolate, m_context);
    Context::Scope context_scope(context);

    // Get global object
    Handle<v8::Object> global = context->Global();
    registerObj(global, obj);
}

Variant JSScriptContext::evaluate(const std::string & code)
{
    // Enter scope
    Locker locker(m_isolate);
    HandleScope scope(m_isolate);

    // Get global context
    Local<Context> context = Local<Context>::New(m_isolate, m_context);
    Context::Scope context_scope(context);

    // Create and compile script
    Handle<String> source = String::NewFromUtf8(m_isolate, code.c_str());
    Handle<Script> script = Script::Compile(source);

    // Run script
    TryCatch trycatch;
    Handle<Value> result = script->Run();
    if (result.IsEmpty()) {
        Handle<Value> ex = trycatch.Exception();
        String::Utf8Value str(ex);
        m_scriptContext->scriptException(std::string(*str));
        return Variant();
    } else return fromV8Value(m_isolate, result);
}

void JSScriptContext::registerObj(Handle<v8::Object> parent, PropertyGroup * obj)
{
    // Create object template
    Handle<ObjectTemplate> templ = ObjectTemplate::New();
    templ->SetInternalFieldCount(1);

    // Register object properties
    for (unsigned int i=0; i<obj->count(); i++) {
        // Get property
        AbstractProperty * prop = obj->at(i);
        std::string name = prop->name();

        // Check if property is a property group
        PropertyGroup * group = dynamic_cast< PropertyGroup * >(prop);
        if (!group) {
            // Add accessor for property
            Local<String> str = String::NewFromUtf8(m_isolate, name.c_str());
            templ->SetAccessor(str, getProperty, setProperty);
        }
    }

    // Register object functions
    reflectionzeug::Object * scriptable = dynamic_cast<reflectionzeug::Object *>(obj);
    if (scriptable) {
        const std::vector<AbstractFunction *> & funcs = scriptable->functions();
        for (std::vector<AbstractFunction *>::const_iterator it = funcs.begin(); it != funcs.end(); ++it) {
            AbstractFunction * func = *it;

            // Bind pointer to AbstractFunction as an external data object
            // and set it in the function template
            Handle<External> func_ptr = External::New(m_isolate, func);
            Handle<FunctionTemplate> funcTempl =
                FunctionTemplate::New(m_isolate, wrapFunction, func_ptr);

            // Register function at object template
            Handle<v8::Function> funcObj = funcTempl->GetFunction();
            templ->Set(String::NewFromUtf8(m_isolate, func->name().c_str()), funcObj);
        }
    }

    // Make persistent template handle
    Persistent<ObjectTemplate> class_template;
    class_template.Reset(m_isolate, templ);

    // Create new object
    Handle<v8::Object> object  = templ->NewInstance();
    Handle<External>   obj_ptr = External::New(m_isolate, obj);
    object->SetInternalField(0, obj_ptr);

    // Register sub-objects
    for (unsigned int i=0; i<obj->count(); i++) {
        // Get property
        AbstractProperty * prop = obj->at(i);
        std::string name = prop->name();
        if (PropertyGroup * group = dynamic_cast< PropertyGroup * >(prop)) {
            // Add sub object
            registerObj(object, group);
        }
    }

    // Register object at parent
    parent->Set(String::NewFromUtf8(m_isolate, obj->name().c_str()), object, ReadOnly);
}


} // namespace scriptzeug
