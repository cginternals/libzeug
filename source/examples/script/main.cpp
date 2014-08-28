#include <array>
#include <iostream>
#include <reflectionzeug/Object.h>
#include <scriptzeug/ScriptContext.h>


using namespace reflectionzeug;
using namespace scriptzeug;
using namespace std;


Variant testFunction(std::string a)
{
    std::cout << "Test function\n";

    VariantMap map;
    map.insert({ "a", Variant(1) });
    map.insert({ "b", Variant(2) });
    map.insert({ "c", Variant(3) });
    map.insert({ "d", Variant("end") });
    return Variant(map);
}


class Counting : public Object
{
public:
    Counting() : Object("counting"), m_min(0), m_max(2)
    {
        addProperty<int>("min", this, &Counting::getMin, &Counting::setMin);
        addProperty<int>("max", this, &Counting::getMax, &Counting::setMax);
        addFunction("count", this, &Counting::count);
    }

    ~Counting()
    {
    }

    void count()
    {
        for (int i=m_min; i<=m_max; i++) {
            std::cout << "Counting " << i << " ...\n";
        }
    }

    int getMin() const { return m_min; }
    void setMin(const int &min) { m_min = min; }
    int getMax() const { return m_max; }
    void setMax(const int & max) { m_max = max; }

protected:
    int m_min, m_max;
};


class MyInterface : public Object
{
public:
    MyInterface() : Object("api"), m_prompt("Hello World")
    {
        // Properties
        addProperty<std::string>("prompt", this, &MyInterface::prompt, &MyInterface::setPrompt);
        addProperty(new Counting);

        // Functions
        addFunction("test",                &testFunction);
        addFunction("helloWorld",    this, &MyInterface::helloWorld);
        addFunction("bottlesOfBeer", this, &MyInterface::bottlesOfBeer);
        addFunction("dynamicTest",   this, &MyInterface::dynamicTest);
    }

    ~MyInterface()
    {
    }

    int helloWorld()
    {
        std::cout << m_prompt << "\n";
        return 10;
    }

    std::string bottlesOfBeer(int count, float a)
    {
        std::cout << count << " bottles of beer with " << a << "% volume.\n";
        return "hicks";
    }

    void dynamicTest(const std::vector<Variant> &args)
    {
        std::cout << "Number of arguments: " << args.size() << "\n";

        int i=0;
        for (std::vector<Variant>::const_iterator it = args.begin(); it != args.end(); ++it) {
            std::cout << "- " << i << ": " << (*it).value<std::string>() << "\n";
            i++;
        }
    }

protected:
    std::string prompt() const
    {
        return m_prompt;
    }

    void setPrompt(const std::string & prompt)
    {
        m_prompt = prompt;
    }

protected:
    std::string m_prompt;
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
        addProperty< array<int, 3> >   ("array",   this, &MyObject::getArray,     &MyObject::setArray);
    }

    ~MyObject()
    {
    }

    char getChar() const { return m_char; }
    void setChar(char c) { m_char = c; std::cout << "m_char = " << (int)m_char << "\n"; }
    unsigned char getUChar() const { return m_uchar; }
    void setUChar(unsigned char c) { m_uchar = c; std::cout << "m_uchar = " << (int)m_uchar << "\n"; }
    int getInt() const { return m_int; }
    void setInt(int n) { m_int = n; std::cout << "m_int = " << m_int << "\n"; }
    unsigned int getUInt() const { return m_uint; }
    void setUInt(unsigned int n) { m_uint = n; std::cout << "m_uint = " << m_uint << "\n"; }
    long getLong() const { return m_long; }
    void setLong(long n) { m_long = n; std::cout << "m_long = " << m_long << "\n"; }
    unsigned long getULong() const { return m_ulong; }
    void setULong(unsigned long n) { m_ulong = n; std::cout << "m_ulong = " << m_ulong << "\n"; }
    long long getLongLong() const { return m_longlong; }
    void setLongLong(long long n) { m_longlong = n; std::cout << "m_longlong = " << m_longlong << "\n"; }
    unsigned long long getULongLong() const { return m_ulonglong; }
    void setULongLong(unsigned long long n) { m_ulonglong = n; std::cout << "m_ulonglong = " << m_ulonglong << "\n"; }
    float getFloat() const { return m_float; }
    void setFloat(float f) { m_float = f; std::cout << "m_float = " << m_float << "\n"; }
    double getDouble() const { return m_double; }
    void setDouble(double d) { m_double = d; std::cout << "m_double = " << m_double << "\n"; }
    bool getBool() const { return m_bool; }
    void setBool(bool b) { m_bool = b; std::cout << "m_bool = " << m_bool << "\n"; }
    std::string getString() const { return m_string; }
    void setString(const std::string & str) { m_string = str; std::cout << "m_string = " << m_string << "\n"; }
    FilePath getPath() const { return m_path; }
    void setPath(const FilePath & path) { m_path = path; std::cout << "m_path = " << m_path.toString() << "\n"; }
    Color getColor() const { return m_color; }
    void setColor(const Color & color) { m_color = color; std::cout << "m_color = " << m_color.toString() << "\n"; }
    Enum getEnum() const { return m_enum; }
    void setEnum(const Enum & value) { m_enum = value; std::cout << "m_enum = " << (int)m_enum << "\n"; }
    int getArray(size_t index) const { return m_array[index]; }
    void setArray(size_t index, int value) { m_array[index] = value; std::cout << "m_array = [" << m_array[0] << ", " << m_array[1] << ", " << m_array[2] << "]\n"; }

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
    array<int, 3> m_array;
};

int main(int argc, char const *argv[])
{
    Variant value;

    // Create scripting context, register exception callback
    ScriptContext scripting;
    scripting.scriptException.connect( [] (const std::string & error) -> void {
        std::cout << "-- EXCEPTION: " << error << "--\n";
    });

    // Register test object
    MyObject obj;
    scripting.registerObject(&obj);

    // Register test API
    MyInterface api;
    scripting.registerObject(&api);

    //
    // Test scripting in general
    //

    std::cout << "1 + 2\n";
    value = scripting.evaluate("1 + 2");
    std::cout << "(1 + 2) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.noFunction();\n";
    value = scripting.evaluate("api.noFunction()");
    std::cout << "--> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "asd\n";
    value = scripting.evaluate("asd");
    std::cout << "--> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    //
    // Test property accessors
    //

    // Display all values once
    value = scripting.evaluate("obj");
    std::cout << "(obj)      --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.char");
    std::cout << "(obj.char) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.uchar");
    std::cout << "(obj.uchar) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.int");
    std::cout << "(obj.int) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.uint");
    std::cout << "(obj.uint) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.long");
    std::cout << "(obj.long) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.ulong");
    std::cout << "(obj.ulong) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.longlong");
    std::cout << "(obj.longlong) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.ulonglong");
    std::cout << "(obj.ulonglong) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.float");
    std::cout << "(obj.float) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.double");
    std::cout << "(obj.double) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.bool");
    std::cout << "(obj.bool) --> " << value.value<std::string>() << "\n";
    value = scripting.evaluate("obj.string");
    std::cout << "(obj.string) --> '" << value.value<std::string>() << "'\n";
    value = scripting.evaluate("obj.path");
    std::cout << "(obj.path) --> '" << value.value<std::string>() << "'\n";
    value = scripting.evaluate("obj.color");
    std::cout << "(obj.color) --> '" << value.value<std::string>() << "'\n";
    value = scripting.evaluate("obj.enum");
    std::cout << "(obj.enum) --> '" << value.value<std::string>() << "'\n";
    value = scripting.evaluate("obj.array");
    std::cout << "(obj.array) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    // Change values
    std::cout << "obj.char = 127\n";
    value = scripting.evaluate("obj.char = 127;");
    value = scripting.evaluate("obj.char");
    std::cout << "(obj.char) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.uchar = 212\n";
    value = scripting.evaluate("obj.uchar = 212;");
    value = scripting.evaluate("obj.uchar");
    std::cout << "(obj.uchar) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.int = -30\n";
    value = scripting.evaluate("obj.int = -30;");
    value = scripting.evaluate("obj.int");
    std::cout << "(obj.int) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.uint = 64738\n";
    value = scripting.evaluate("obj.uint = 64738;");
    value = scripting.evaluate("obj.uint");
    std::cout << "(obj.uint) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.long = -1024 * 1024\n";
    value = scripting.evaluate("obj.long = -1024 * 1024;");
    value = scripting.evaluate("obj.long");
    std::cout << "(obj.long) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.ulong = 1024 * 1024\n";
    value = scripting.evaluate("obj.ulong = 1024 * 1024;");
    value = scripting.evaluate("obj.ulong");
    std::cout << "(obj.ulong) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.longlong = -1024 * 1024\n";
    value = scripting.evaluate("obj.longlong = -1024 * 1024;");
    value = scripting.evaluate("obj.longlong");
    std::cout << "(obj.longlong) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.ulonglong = 1024 * 1024\n";
    value = scripting.evaluate("obj.ulonglong = 1024 * 1024;");
    value = scripting.evaluate("obj.ulonglong");
    std::cout << "(obj.ulonglong) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.float = -3.14\n";
    value = scripting.evaluate("obj.float = -3.14;");
    value = scripting.evaluate("obj.float");
    std::cout << "(obj.float) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.double = Math.PI\n";
    value = scripting.evaluate("obj.double = Math.PI;");
    value = scripting.evaluate("obj.double");
    std::cout << "(obj.double) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.bool = true\n";
    value = scripting.evaluate("obj.bool = true;");
    value = scripting.evaluate("obj.bool");
    std::cout << "(obj.bool) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "obj.string = 'whatever'\n";
    value = scripting.evaluate("obj.string = 'whatever';");
    value = scripting.evaluate("obj.string");
    std::cout << "(obj.string) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.path = '/path/to/some/thing'\n";
    value = scripting.evaluate("obj.path = '/path/to/some/thing';");
    value = scripting.evaluate("obj.path");
    std::cout << "(obj.path) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.color = '#ff6600ff'\n";
    value = scripting.evaluate("obj.color = '#ff6600ff';");
    value = scripting.evaluate("obj.color");
    std::cout << "(obj.color) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.color = [10, 10, 80, 255]\n";
    value = scripting.evaluate("obj.color = [10, 10, 80, 255];");
    value = scripting.evaluate("obj.color");
    std::cout << "(obj.color) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.color = []\n";
    value = scripting.evaluate("obj.color = [];");
    value = scripting.evaluate("obj.color");
    std::cout << "(obj.color) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.color = {r: 10, g: 50, b: 100, a: 120}\n";
    value = scripting.evaluate("obj.color = {r: '10', g: 50, b: 100, a: 120};");
    value = scripting.evaluate("obj.color");
    std::cout << "(obj.color) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.color = {}\n";
    value = scripting.evaluate("obj.color = {};");
    value = scripting.evaluate("obj.color");
    std::cout << "(obj.color) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.enum = 'Choice3'\n";
    value = scripting.evaluate("obj.enum = 'Choice3';");
    value = scripting.evaluate("obj.enum");
    std::cout << "(obj.enum) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.enum = 'Choice5'\n";
    value = scripting.evaluate("obj.enum = 'Choice5';");
    value = scripting.evaluate("obj.enum");
    std::cout << "(obj.enum) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.array = [4, 5, 6]\n";
    value = scripting.evaluate("obj.array = [4, 5, 6];");
    value = scripting.evaluate("obj.array");
    std::cout << "(obj.array) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.array = [7, 8, 9, 10, 11, 12]\n";
    value = scripting.evaluate("obj.array = [7, 8, 9, 10, 11, 12];");
    value = scripting.evaluate("obj.array");
    std::cout << "(obj.array) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    std::cout << "obj.array = [13, 14]\n";
    value = scripting.evaluate("obj.array = [13, 14];");
    value = scripting.evaluate("obj.array");
    std::cout << "(obj.array) --> '" << value.value<std::string>() << "'\n";
    std::cout << "\n";

    //
    // Test API
    //

    std::cout << "api.prompt = 'Welcome!'\n";
    value = scripting.evaluate("api.prompt = 'Welcome!';");
    std::cout << "--> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.helloWorld() + 1\n";
    value = scripting.evaluate("api.helloWorld() + 1;");
    std::cout << "(11) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.test()\n";
    value = scripting.evaluate("api.test();");
    std::cout << "--> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.bottlesOfBeer(120, 3.5, 10)\n";
    value = scripting.evaluate("api.bottlesOfBeer(120, 3.5, 10);");
    std::cout << "--> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.bottlesOfBeer()\n";
    value = scripting.evaluate("api.bottlesOfBeer();");
    std::cout << "--> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.dynamicTest([3.5, {a: 100, b: 200}, 12], \"asd\")\n";
    value = scripting.evaluate("api.dynamicTest([3.5, {a: 100, b: 200}, 12], \"asd\");");
    std::cout << "\n";

    std::cout << "api.dynamicTest()\n";
    value = scripting.evaluate("api.dynamicTest();");
    std::cout << "\n";

    std::cout << "api.counting.min\n";
    value = scripting.evaluate("api.counting.min;");
    std::cout << "(0) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.counting.max\n";
    value = scripting.evaluate("api.counting.max;");
    std::cout << "(2) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.counting.min = 5\n";
    value = scripting.evaluate("api.counting.min = 5;");
    std::cout << "(5) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.counting.max = 10\n";
    value = scripting.evaluate("api.counting.max = 10;");
    std::cout << "(10) --> " << value.value<std::string>() << "\n";
    std::cout << "\n";

    std::cout << "api.counting.count()\n";
    value = scripting.evaluate("api.counting.count();");
    std::cout << "\n";

    return 0;
}
