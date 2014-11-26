#include <gmock/gmock.h>

#include <array>
#include <iostream>

#include <reflectionzeug/Object.h>
#include <scriptzeug/ScriptContext.h>


using namespace reflectionzeug;
using namespace scriptzeug;


int testFunction()
{
    return 42;
}


class RegisteredObject : public Object
{
public:
    RegisteredObject() : Object("registeredObject")
    {
        addFunction("successor", this, &RegisteredObject::successor);
    }

    ~RegisteredObject()
    {
    }
    
    int successor(int number)
    {
        return number + 1;
    }
};


class MyInterface : public Object
{
public:
    MyInterface() : Object("api")
    {
        // Properties
        addProperty(new RegisteredObject);

        // Functions
        addFunction("test", &testFunction);
        addFunction("countArgs", this, &MyInterface::countArgs);
    }

    ~MyInterface()
    {
    }

    int countArgs(const std::vector<Variant> &args)
    {
        return args.size();
    }
};


class MyObject : public Object
{
public:
    enum Enum {
        Choice1,
        Choice2,
        Choice3
    };

public:
    MyObject()
    : Object("obj")
    , m_char(0)
    , m_uchar(0)
    , m_int(0)
    , m_uint(0)
    , m_long(0)
    , m_ulong(0)
    , m_longlong(0)
    , m_ulonglong(0)
    , m_float(0.0f)
    , m_double(0.0)
    , m_bool(false)
    , m_enum(Choice1)
    , m_array({1, 2, 3})
    {
        // Properties
        addProperty<char>              ("char",      this, &MyObject::getChar,      &MyObject::setChar);
        addProperty<unsigned char>     ("uchar",     this, &MyObject::getUChar,     &MyObject::setUChar);
        addProperty<int>               ("int",       this, &MyObject::getInt,       &MyObject::setInt);
        addProperty<unsigned int>      ("uint",      this, &MyObject::getUInt,      &MyObject::setUInt);
        addProperty<long>              ("long",      this, &MyObject::getLong,      &MyObject::setLong);
        addProperty<unsigned long>     ("ulong",     this, &MyObject::getULong,     &MyObject::setULong);
        addProperty<long long>         ("longlong",  this, &MyObject::getLongLong,  &MyObject::setLongLong);
        addProperty<unsigned long long>("ulonglong", this, &MyObject::getULongLong, &MyObject::setULongLong);
        addProperty<float>             ("float",     this, &MyObject::getFloat,     &MyObject::setFloat);
        addProperty<double>            ("double",    this, &MyObject::getDouble,    &MyObject::setDouble);
        addProperty<bool>              ("bool",      this, &MyObject::getBool,      &MyObject::setBool);
        addProperty<std::string>       ("string",    this, &MyObject::getString,    &MyObject::setString);
        addProperty<FilePath>          ("path",      this, &MyObject::getPath,      &MyObject::setPath);
        addProperty<Color>             ("color",     this, &MyObject::getColor,     &MyObject::setColor);
        addProperty<Enum>              ("enum",      this, &MyObject::getEnum,      &MyObject::setEnum);
        this->property<Enum>("enum")->setStrings({
            { Enum::Choice1, "Choice1" },
            { Enum::Choice2, "Choice2" },
            { Enum::Choice3, "Choice3" }
        });
        addProperty< std::array<int, 3> >   ("array",   this, &MyObject::getArray,     &MyObject::setArray);
    }

    ~MyObject()
    {
    }

    char getChar() const { return m_char; }
    void setChar(char c) { m_char = c;}
    unsigned char getUChar() const { return m_uchar; }
    void setUChar(unsigned char c) { m_uchar = c;}
    int getInt() const { return m_int; }
    void setInt(int n) { m_int = n;}
    unsigned int getUInt() const { return m_uint; }
    void setUInt(unsigned int n) { m_uint = n;}
    long getLong() const { return m_long; }
    void setLong(long n) { m_long = n;}
    unsigned long getULong() const { return m_ulong; }
    void setULong(unsigned long n) { m_ulong = n;}
    long long getLongLong() const { return m_longlong; }
    void setLongLong(long long n) { m_longlong = n;}
    unsigned long long getULongLong() const { return m_ulonglong; }
    void setULongLong(unsigned long long n) { m_ulonglong = n;}
    float getFloat() const { return m_float; }
    void setFloat(float f) { m_float = f;}
    double getDouble() const { return m_double; }
    void setDouble(double d) { m_double = d;}
    bool getBool() const { return m_bool; }
    void setBool(bool b) { m_bool = b;}
    std::string getString() const { return m_string; }
    void setString(const std::string & str) { m_string = str;}
    FilePath getPath() const { return m_path; }
    void setPath(const FilePath & path) { m_path = path;}
    Color getColor() const { return m_color; }
    void setColor(const Color & color) { m_color = color;}
    Enum getEnum() const { return m_enum; }
    void setEnum(const Enum & value) { m_enum = value;}
    int getArray(size_t index) const { return m_array[index]; }
    void setArray(size_t index, int value) { m_array[index] = value;}

protected:
    // Property values
    char          m_char;
    unsigned char m_uchar;
    int           m_int;
    unsigned int  m_uint;
    long          m_long;
    unsigned long m_ulong;
    long long     m_longlong;
    unsigned long long m_ulonglong;
    float         m_float;
    double        m_double;
    bool          m_bool;
    std::string   m_string;
    FilePath      m_path;
    Color         m_color;
    Enum          m_enum;
    std::array<int, 3> m_array;
};


class ScriptContext_test : public testing::Test
{
public:
protected:
    ScriptContext m_scripting;
};

TEST_F(ScriptContext_test, Evaluate)
{
    std::string errorCatch;
    Variant value;

    m_scripting.scriptException.connect( [&] (const std::string & error) -> void {
        errorCatch = error;
    });

    value = m_scripting.evaluate("1 + 2");
    ASSERT_EQ(3, value.value<int>());

    value = m_scripting.evaluate("asd");
    ASSERT_TRUE(value.isNull());
    ASSERT_EQ("ReferenceError: identifier 'asd' undefined", errorCatch);
}

TEST_F(ScriptContext_test, RegisterObject_Getter)
{
    Variant value;
    MyObject obj;

    m_scripting.registerObject(&obj);

    value = m_scripting.evaluate("obj.char");
    ASSERT_EQ(obj.getChar(), value.value<char>());
    value = m_scripting.evaluate("obj.uchar");
    ASSERT_EQ(obj.getUChar(), value.value<unsigned char>());
    value = m_scripting.evaluate("obj.int");
    ASSERT_EQ(obj.getInt(), value.value<int>());
    value = m_scripting.evaluate("obj.uint");
    ASSERT_EQ(obj.getUInt(), value.value<unsigned int>());
    value = m_scripting.evaluate("obj.long");
    ASSERT_EQ(obj.getLong(), value.value<long>());
    value = m_scripting.evaluate("obj.ulong");
    ASSERT_EQ(obj.getULong(), value.value<unsigned long>());
    value = m_scripting.evaluate("obj.longlong");
    ASSERT_EQ(obj.getLongLong(), value.value<long long>());
    value = m_scripting.evaluate("obj.ulonglong");
    ASSERT_EQ(obj.getULongLong(), value.value<unsigned long long>());
    value = m_scripting.evaluate("obj.float");
    ASSERT_EQ(obj.getFloat(), value.value<float>());
    value = m_scripting.evaluate("obj.double");
    ASSERT_EQ(obj.getDouble(), value.value<double>());
    value = m_scripting.evaluate("obj.bool");
    ASSERT_EQ(obj.getBool(), value.value<bool>());
    value = m_scripting.evaluate("obj.string");
    ASSERT_EQ(obj.getString(), value.value<std::string>());
    value = m_scripting.evaluate("obj.path");
    ASSERT_EQ(obj.getPath().string(), value.value<std::string>());
    value = m_scripting.evaluate("obj.color");
    ASSERT_EQ(obj.getColor().toString(), value.value<std::string>());
    value = m_scripting.evaluate("obj.enum");
    ASSERT_EQ("Choice1", value.value<std::string>());

    value = m_scripting.evaluate("obj.array");
    VariantArray varArray = value.value<VariantArray>();
    for (size_t i = 0; i < varArray.size(); ++i)
    {
        ASSERT_EQ(obj.getArray(i), varArray[i].value<int>());
    }
}

TEST_F(ScriptContext_test, RegisterObject_Setter)
{
    Variant value;
    MyObject obj;

    m_scripting.registerObject(&obj);

    m_scripting.evaluate("obj.char = 127;");
    value = m_scripting.evaluate("obj.char");
    ASSERT_EQ(obj.getChar(), value.value<char>());
    m_scripting.evaluate("obj.uchar = 212;");
    value = m_scripting.evaluate("obj.uchar");
    ASSERT_EQ(obj.getUChar(), value.value<unsigned char>());
    m_scripting.evaluate("obj.int = -30;");
    value = m_scripting.evaluate("obj.int");
    ASSERT_EQ(obj.getInt(), value.value<int>());
    m_scripting.evaluate("obj.uint = 647380;");
    value = m_scripting.evaluate("obj.uint");
    ASSERT_EQ(obj.getUInt(), value.value<unsigned int>());
    m_scripting.evaluate("obj.long = -1024 * 1024;");
    value = m_scripting.evaluate("obj.long");
    ASSERT_EQ(obj.getLong(), value.value<long>());
    m_scripting.evaluate("obj.ulong = 1024 * 1024;");
    value = m_scripting.evaluate("obj.ulong");
    ASSERT_EQ(obj.getULong(), value.value<unsigned long>());
    m_scripting.evaluate("obj.longlong = -1024 * 1024;");
    value = m_scripting.evaluate("obj.longlong");
    ASSERT_EQ(obj.getLongLong(), value.value<long long>());
    m_scripting.evaluate("obj.ulonglong 1024 * 1024;");
    value = m_scripting.evaluate("obj.ulonglong");
    ASSERT_EQ(obj.getULongLong(), value.value<unsigned long long>());
    m_scripting.evaluate("obj.float = -3.14");
    value = m_scripting.evaluate("obj.float");
    ASSERT_EQ(obj.getFloat(), value.value<float>());
    m_scripting.evaluate("obj.double = Math.PI;");
    value = m_scripting.evaluate("obj.double");
    ASSERT_EQ(obj.getDouble(), value.value<double>());
    m_scripting.evaluate("obj.bool = true;");
    value = m_scripting.evaluate("obj.bool");
    ASSERT_EQ(obj.getBool(), value.value<bool>());
    m_scripting.evaluate("obj.string = 'checkstring';");
    value = m_scripting.evaluate("obj.string");
    ASSERT_EQ(obj.getString(), value.value<std::string>());
    m_scripting.evaluate("obj.path = '/path/to/some/thing';");
    value =  m_scripting.evaluate("obj.path");
    ASSERT_EQ(obj.getPath().string(), value.value<std::string>());

    m_scripting.evaluate("obj.color = '#ff6600ff';");
    value = m_scripting.evaluate("obj.color");
    ASSERT_EQ(obj.getColor().toString(), value.value<std::string>());
    m_scripting.evaluate("obj.color = [10, 10, 80, 255];");
    value = m_scripting.evaluate("obj.color");
    ASSERT_EQ(obj.getColor().toString(), value.value<std::string>());
    m_scripting.evaluate("obj.color = [];");
    value = m_scripting.evaluate("obj.color");
    ASSERT_EQ(obj.getColor().toString(), value.value<std::string>());
    m_scripting.evaluate("obj.color = {r: '10', g: 50, b: 100, a: 120};");
    value = m_scripting.evaluate("obj.color");
    ASSERT_EQ(obj.getColor().toString(), value.value<std::string>());
    m_scripting.evaluate("obj.color = {};");
    value = m_scripting.evaluate("obj.color");
    ASSERT_EQ(obj.getColor().toString(), value.value<std::string>());

    m_scripting.evaluate("obj.enum = 'Choice3';");
    value = m_scripting.evaluate("obj.enum");
    ASSERT_EQ(MyObject::Enum::Choice3, obj.getEnum());
    ASSERT_EQ("Choice3", value.value<std::string>());
    m_scripting.evaluate("obj.enum = 'Choice5';");
    value = m_scripting.evaluate("obj.enum");
    ASSERT_EQ(MyObject::Enum::Choice3, obj.getEnum());
    ASSERT_EQ("Choice3", value.value<std::string>());

    m_scripting.evaluate("obj.array = [4, 5, 6];");
    value = m_scripting.evaluate("obj.array");
    VariantArray varArray = value.value<VariantArray>();
    for (size_t i = 0; i < varArray.size(); ++i)
    {
        ASSERT_EQ(obj.getArray(i), varArray[i].value<int>());
    }
    m_scripting.evaluate("obj.array = [7, 8, 9, 10, 11, 12];");
    value = m_scripting.evaluate("obj.array");
    varArray = value.value<VariantArray>();
    for (size_t i = 0; i < varArray.size(); ++i)
    {
        ASSERT_EQ(obj.getArray(i), varArray[i].value<int>());
    }
    m_scripting.evaluate("obj.array = [13, 14];");
    value = m_scripting.evaluate("obj.array");
    varArray = value.value<VariantArray>();
    for (size_t i = 0; i < varArray.size(); ++i)
    {
        ASSERT_EQ(obj.getArray(i), varArray[i].value<int>());
    }
}

TEST_F(ScriptContext_test, RegisterObject_Methods)
{
    std::string errorCatch;
    Variant value;
    MyInterface api;

    m_scripting.scriptException.connect( [&] (const std::string & error) -> void {
        errorCatch = error;
    });

    m_scripting.registerObject(&api);

    value = m_scripting.evaluate("api.noFunction();");
    ASSERT_TRUE(value.isNull());
    ASSERT_EQ("TypeError: call target not an object", errorCatch);

    value = m_scripting.evaluate("api.test();");
    ASSERT_EQ(42, value.value<int>());

    value = m_scripting.evaluate("api.countArgs([3.5, {a: 100, b: 200}, 12], \"asd\");");
    ASSERT_EQ(2, value.value<int>());
    value = m_scripting.evaluate("api.countArgs();");
    ASSERT_EQ(0, value.value<int>());

    value = m_scripting.evaluate("api.registeredObject.successor(6);");
    ASSERT_EQ(7, value.value<int>());
}
