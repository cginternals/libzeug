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
    virtual void SetUp()
    {
        m_scripting.registerObject(&m_obj);

        m_scripting.scriptException.connect( [this] (const std::string & error) -> void {
            m_error = error;
        });
    }

    ScriptContext m_scripting;
    MyObject m_obj;
    Variant m_result;
    std::string m_error;
};

TEST_F(ScriptContext_test, Evaluate)
{
    m_result = m_scripting.evaluate("1 + 2");
    ASSERT_EQ(3, m_result.value<int>());

    m_result = m_scripting.evaluate("asd");
    ASSERT_TRUE(m_result.isNull());
    ASSERT_EQ("ReferenceError: identifier 'asd' undefined", m_error);
}

TEST_F(ScriptContext_test, RegisterObject_Getter)
{
    m_result = m_scripting.evaluate("obj.char");
    ASSERT_EQ(m_obj.getChar(), m_result.value<char>());
    m_result = m_scripting.evaluate("obj.uchar");
    ASSERT_EQ(m_obj.getUChar(), m_result.value<unsigned char>());
    m_result = m_scripting.evaluate("obj.int");
    ASSERT_EQ(m_obj.getInt(), m_result.value<int>());
    m_result = m_scripting.evaluate("obj.uint");
    ASSERT_EQ(m_obj.getUInt(), m_result.value<unsigned int>());
    m_result = m_scripting.evaluate("obj.long");
    ASSERT_EQ(m_obj.getLong(), m_result.value<long>());
    m_result = m_scripting.evaluate("obj.ulong");
    ASSERT_EQ(m_obj.getULong(), m_result.value<unsigned long>());
    m_result = m_scripting.evaluate("obj.longlong");
    ASSERT_EQ(m_obj.getLongLong(), m_result.value<long long>());
    m_result = m_scripting.evaluate("obj.ulonglong");
    ASSERT_EQ(m_obj.getULongLong(), m_result.value<unsigned long long>());
    m_result = m_scripting.evaluate("obj.float");
    ASSERT_EQ(m_obj.getFloat(), m_result.value<float>());
    m_result = m_scripting.evaluate("obj.double");
    ASSERT_EQ(m_obj.getDouble(), m_result.value<double>());
    m_result = m_scripting.evaluate("obj.bool");
    ASSERT_EQ(m_obj.getBool(), m_result.value<bool>());
    m_result = m_scripting.evaluate("obj.string");
    ASSERT_EQ(m_obj.getString(), m_result.value<std::string>());
    m_result = m_scripting.evaluate("obj.path");
    ASSERT_EQ(m_obj.getPath().string(), m_result.value<std::string>());
    m_result = m_scripting.evaluate("obj.color");
    ASSERT_EQ(m_obj.getColor().toString(), m_result.value<std::string>());
    m_result = m_scripting.evaluate("obj.enum");
    ASSERT_EQ("Choice1", m_result.value<std::string>());

    m_result = m_scripting.evaluate("obj.array");
    VariantArray varArray = m_result.value<VariantArray>();
    for (size_t i = 0; i < varArray.size(); ++i)
    {
        ASSERT_EQ(m_obj.getArray(i), varArray[i].value<int>());
    }
}

TEST_F(ScriptContext_test, RegisterObject_Setter)
{
    m_scripting.evaluate("obj.char = 127;");
    m_result = m_scripting.evaluate("obj.char");
    ASSERT_EQ(m_obj.getChar(), m_result.value<char>());
    m_scripting.evaluate("obj.uchar = 212;");
    m_result = m_scripting.evaluate("obj.uchar");
    ASSERT_EQ(m_obj.getUChar(), m_result.value<unsigned char>());
    m_scripting.evaluate("obj.int = -30;");
    m_result = m_scripting.evaluate("obj.int");
    ASSERT_EQ(m_obj.getInt(), m_result.value<int>());
    m_scripting.evaluate("obj.uint = 647380;");
    m_result = m_scripting.evaluate("obj.uint");
    ASSERT_EQ(m_obj.getUInt(), m_result.value<unsigned int>());
    m_scripting.evaluate("obj.long = -1024 * 1024;");
    m_result = m_scripting.evaluate("obj.long");
    ASSERT_EQ(m_obj.getLong(), m_result.value<long>());
    m_scripting.evaluate("obj.ulong = 1024 * 1024;");
    m_result = m_scripting.evaluate("obj.ulong");
    ASSERT_EQ(m_obj.getULong(), m_result.value<unsigned long>());
    m_scripting.evaluate("obj.longlong = -1024 * 1024;");
    m_result = m_scripting.evaluate("obj.longlong");
    ASSERT_EQ(m_obj.getLongLong(), m_result.value<long long>());
    m_scripting.evaluate("obj.ulonglong 1024 * 1024;");
    m_result = m_scripting.evaluate("obj.ulonglong");
    ASSERT_EQ(m_obj.getULongLong(), m_result.value<unsigned long long>());
    m_scripting.evaluate("obj.float = -3.14");
    m_result = m_scripting.evaluate("obj.float");
    ASSERT_EQ(m_obj.getFloat(), m_result.value<float>());
    m_scripting.evaluate("obj.double = Math.PI;");
    m_result = m_scripting.evaluate("obj.double");
    ASSERT_EQ(m_obj.getDouble(), m_result.value<double>());
    m_scripting.evaluate("obj.bool = true;");
    m_result = m_scripting.evaluate("obj.bool");
    ASSERT_EQ(m_obj.getBool(), m_result.value<bool>());
    m_scripting.evaluate("obj.string = 'checkstring';");
    m_result = m_scripting.evaluate("obj.string");
    ASSERT_EQ(m_obj.getString(), m_result.value<std::string>());
    m_scripting.evaluate("obj.path = '/path/to/some/thing';");
    m_result =  m_scripting.evaluate("obj.path");
    ASSERT_EQ(m_obj.getPath().string(), m_result.value<std::string>());

    m_scripting.evaluate("obj.color = '#ff6600ff';");
    m_result = m_scripting.evaluate("obj.color");
    ASSERT_EQ(m_obj.getColor().toString(), m_result.value<std::string>());
    m_scripting.evaluate("obj.color = [10, 10, 80, 255];");
    m_result = m_scripting.evaluate("obj.color");
    ASSERT_EQ(m_obj.getColor().toString(), m_result.value<std::string>());
    m_scripting.evaluate("obj.color = [];");
    m_result = m_scripting.evaluate("obj.color");
    ASSERT_EQ(m_obj.getColor().toString(), m_result.value<std::string>());
    m_scripting.evaluate("obj.color = {r: '10', g: 50, b: 100, a: 120};");
    m_result = m_scripting.evaluate("obj.color");
    ASSERT_EQ(m_obj.getColor().toString(), m_result.value<std::string>());
    m_scripting.evaluate("obj.color = {};");
    m_result = m_scripting.evaluate("obj.color");
    ASSERT_EQ(m_obj.getColor().toString(), m_result.value<std::string>());

    m_scripting.evaluate("obj.enum = 'Choice3';");
    m_result = m_scripting.evaluate("obj.enum");
    ASSERT_EQ(MyObject::Enum::Choice3, m_obj.getEnum());
    ASSERT_EQ("Choice3", m_result.value<std::string>());
    m_scripting.evaluate("obj.enum = 'Choice5';");
    m_result = m_scripting.evaluate("obj.enum");
    ASSERT_EQ(MyObject::Enum::Choice3, m_obj.getEnum());
    ASSERT_EQ("Choice3", m_result.value<std::string>());

    m_scripting.evaluate("obj.array = [4, 5, 6];");
    m_result = m_scripting.evaluate("obj.array");
    VariantArray varArray = m_result.value<VariantArray>();
    for (size_t i = 0; i < varArray.size(); ++i)
    {
        ASSERT_EQ(m_obj.getArray(i), varArray[i].value<int>());
    }
    m_scripting.evaluate("obj.array = [7, 8, 9, 10, 11, 12];");
    m_result = m_scripting.evaluate("obj.array");
    varArray = m_result.value<VariantArray>();
    for (size_t i = 0; i < varArray.size(); ++i)
    {
        ASSERT_EQ(m_obj.getArray(i), varArray[i].value<int>());
    }
    m_scripting.evaluate("obj.array = [13, 14];");
    m_result = m_scripting.evaluate("obj.array");
    varArray = m_result.value<VariantArray>();
    for (size_t i = 0; i < varArray.size(); ++i)
    {
        ASSERT_EQ(m_obj.getArray(i), varArray[i].value<int>());
    }
}

TEST_F(ScriptContext_test, RegisterObject_Methods)
{
    MyInterface api;
    m_scripting.registerObject(&api);

    m_result = m_scripting.evaluate("api.noFunction();");
    ASSERT_TRUE(m_result.isNull());
    ASSERT_EQ("TypeError: call target not an object", m_error);

    m_result = m_scripting.evaluate("api.test();");
    ASSERT_EQ(42, m_result.value<int>());

    m_result = m_scripting.evaluate("api.countArgs([3.5, {a: 100, b: 200}, 12], \"asd\");");
    ASSERT_EQ(2, m_result.value<int>());
    m_result = m_scripting.evaluate("api.countArgs();");
    ASSERT_EQ(0, m_result.value<int>());

    m_result = m_scripting.evaluate("api.registeredObject.successor(6);");
    ASSERT_EQ(7, m_result.value<int>());
}
