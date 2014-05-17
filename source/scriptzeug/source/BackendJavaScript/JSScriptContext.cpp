#include <functional>
#include <reflectionzeug/Object.h>
#include <reflectionzeug/Variant.h>
#include "scriptzeug/ScriptContext.h"
#include "BackendJavaScript/JSScriptContext.h"


using namespace v8;
using namespace reflectionzeug;
namespace scriptzeug
{


static Variant fromV8Value(Local<Value> arg)
{
    // Int
    if (arg->IsInt32()) {
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
        Variant value(Variant::TypeArray);
        Handle<Array> arr = Handle<Array>::Cast(arg);
        for (unsigned int i=0; i<arr->Length(); i++) {
            Local<Value> prop = arr->Get(i);
            value.set(i, fromV8Value(prop));
        }
        return value;
    }

    // Object
    else if (arg->IsObject()) {
        Variant value(Variant::TypeObject);
        Local<v8::Object> obj = arg->ToObject();
        Local<Array> props = obj->GetPropertyNames();
        for (unsigned int i=0; i<props->Length(); i++) {
            Local<Value> name = props->Get(i);
            String::Utf8Value ascii(name);
            std::string propName(*ascii);
            Local<Value> prop = obj->Get(name);
            value.set(propName, fromV8Value(prop));
        }
        return value;
    }

    // Undefined
    return Variant();
}

static Local<Value> toV8Value(Isolate *isolate, const Variant &arg)
{
    Local<Value> value;

    if (arg.type() == Variant::TypeInt) {
        Local<Integer> v = Integer::New(isolate, arg.toInt());
        value = v;
    }

    else if (arg.type() == Variant::TypeUInt) {
        Local<Integer> v = Integer::NewFromUnsigned(isolate, arg.toUInt());
        value = v;
    }

    else if (arg.type() == Variant::TypeDouble) {
        Local<Number> v = Number::New(isolate, arg.toDouble());
        value = v;
    }

    else if (arg.type() == Variant::TypeBool) {
        Local<Boolean> v = Boolean::New(isolate, arg.toBool());
        value = v;
    }

    else if (arg.type() == Variant::TypeString) {
        Handle<String> str = String::NewFromUtf8(isolate, arg.toString().c_str());
        value = str;
    }

    else if (arg.type() == Variant::TypeArray) {
        Handle<Array> arr = Array::New(isolate, arg.size());
        for (unsigned int i=0; i<arg.size(); i++) {
            arr->Set(i, toV8Value(isolate, arg.get(i)));
        }
        value = arr;
    }

    else if (arg.type() == Variant::TypeObject) {
        Handle<v8::Object> obj = v8::Object::New(isolate);
        std::vector<std::string> args = arg.keys();
        for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {
            std::string name = *it;
            Handle<String> n = String::NewFromUtf8(isolate, name.c_str());
            obj->Set(n, toV8Value(isolate, arg.get(name)));
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
        arguments.push_back(fromV8Value(arg));
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
        value = (bool)prop->value();
    }

    // Unsigned integral
    else if (UnsignedIntegralPropertyInterface * prop = dynamic_cast< UnsignedIntegralPropertyInterface * >(property) ) {
        value = (unsigned int)prop->toULongLong();
    }

    // Signed integral
    else if (SignedIntegralPropertyInterface * prop = dynamic_cast< SignedIntegralPropertyInterface * >(property) ) {
        value = (int)prop->toULongLong();
    }

    // Floating point number
    else if (FloatingPointPropertyInterface * prop = dynamic_cast< FloatingPointPropertyInterface * >(property) ) {
        value = (double)prop->toDouble();
    }

    // Enum
    else if (EnumPropertyInterface * prop = dynamic_cast< EnumPropertyInterface * >(property) ) {
        value = prop->toString();
    }

    // String
    else if (StringPropertyInterface * prop = dynamic_cast< StringPropertyInterface * >(property) ) {
        value = prop->toString();
    }

    // FilePath
    else if (Property<FilePath> * prop = dynamic_cast< Property<FilePath> * >(property) ) {
        value = prop->value().toString();
    }

    // Color
    else if (ColorPropertyInterface * prop = dynamic_cast< ColorPropertyInterface * >(property) ) {
        value = prop->toColor().toString();
    }

    // Array
    else if (AbstractPropertyCollection * prop = dynamic_cast< AbstractPropertyCollection * >(property) ) {
        value = Variant::Array();
        for (size_t i=0; i<prop->count(); i++) {
            AbstractProperty * subprop = prop->at(i);
            value.append(getPropertyValue(subprop));
        }
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
            prop->setValue( value.toBool() );
        }

        // Unsigned integral
        else if (UnsignedIntegralPropertyInterface * prop = dynamic_cast< UnsignedIntegralPropertyInterface * >(property) ) {
            prop->fromULongLong( value.toUInt() );
        }

        // Signed integral
        else if (SignedIntegralPropertyInterface * prop = dynamic_cast< SignedIntegralPropertyInterface * >(property) ) {
            prop->fromULongLong( value.toInt() );
        }

        // Floating point number
        else if (FloatingPointPropertyInterface * prop = dynamic_cast< FloatingPointPropertyInterface * >(property) ) {
            prop->fromDouble( value.toDouble() );
        }

        // Enum
        else if (EnumPropertyInterface * prop = dynamic_cast< EnumPropertyInterface * >(property) ) {
            prop->fromString( value.toString() );
        }

        // String
        else if (StringPropertyInterface * prop = dynamic_cast< StringPropertyInterface * >(property) ) {
            prop->fromString( value.toString() );
        }

        // FilePath
        else if (Property<FilePath> * prop = dynamic_cast< Property<FilePath> * >(property) ) {
            prop->setValue( value.toString() );
        }

        // Color
        else if (ColorPropertyInterface * prop = dynamic_cast< ColorPropertyInterface * >(property) ) {
            if (value.isArray()) {
                int r = value.get(0).toInt();
                int g = value.get(1).toInt();
                int b = value.get(2).toInt();
                int a = value.get(3).toInt();
                prop->fromColor(Color(r, g, b, a));
            } else if (value.isObject()) {
                int r = value.get("r").toInt();
                int g = value.get("g").toInt();
                int b = value.get("b").toInt();
                int a = value.get("a").toInt();
                prop->fromColor(Color(r, g, b, a));
            } else {
                prop->fromString(value.toString());
            }
        }

        // Array
        else if (AbstractPropertyCollection * prop = dynamic_cast< AbstractPropertyCollection * >(property) ) {
            if (value.isArray()) {
                for (size_t i=0; i<(size_t)value.size() && i<prop->count(); i++) {
                    AbstractProperty * subprop = prop->at(i);
                    setPropertyValue(subprop, value.get(i));
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
    // Convert value into variant
    Variant v = fromV8Value(value);

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
    } else return fromV8Value(result);
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
