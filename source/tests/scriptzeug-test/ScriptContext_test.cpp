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


class ScriptContext_test : public testing::Test
{
public:
protected:
    virtual void SetUp()
    {
        m_scripting.registerObject(&m_api);

        m_scripting.scriptException.connect( [this] (const std::string & error) -> void {
            m_error = error;
        });
    }

    ScriptContext m_scripting;
    MyInterface m_api;
    Variant m_result;
    std::string m_error;
};


TEST_F(ScriptContext_test, Evaluate)
{
    m_result = m_scripting.evaluate("1 + 2");
    ASSERT_EQ(3, m_result.value<int>());

    m_result = m_scripting.evaluate("'testString'.toUpperCase()");
    ASSERT_EQ("TESTSTRING", m_result.value<std::string>());

}

TEST_F(ScriptContext_test, ErrorHandling)
{
    m_result = m_scripting.evaluate("asd");
    ASSERT_TRUE(m_result.isNull());
    ASSERT_EQ("ReferenceError: identifier 'asd' undefined", m_error);

    m_result = m_scripting.evaluate("api.noFunction();");
    ASSERT_TRUE(m_result.isNull());
    ASSERT_EQ("TypeError: call target not an object", m_error);

    m_result = m_scripting.evaluate("var causesRangeError = new Array(-1);");
    ASSERT_TRUE(m_result.isNull());
    ASSERT_EQ("RangeError: range error (rc -102)", m_error);

    m_result = m_scripting.evaluate("print(1 + 2;");
    ASSERT_TRUE(m_result.isNull());
    ASSERT_EQ("SyntaxError: parse error (line 1)", m_error);
}

TEST_F(ScriptContext_test, RegisterObject_Methods)
{
    m_result = m_scripting.evaluate("api.test();");
    ASSERT_EQ(42, m_result.value<int>());

    m_result = m_scripting.evaluate("api.countArgs([3.5, {a: 100, b: 200}, 12], \"asd\");");
    ASSERT_EQ(2, m_result.value<int>());

    m_result = m_scripting.evaluate("api.countArgs();");
    ASSERT_EQ(0, m_result.value<int>());
}

TEST_F(ScriptContext_test, RegisterObject_SubObjectAccess)
{
    m_result = m_scripting.evaluate("api.registeredObject.successor(6);");
    ASSERT_EQ(7, m_result.value<int>());
}
