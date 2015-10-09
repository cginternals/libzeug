
#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceString_test : public testing::Test
{
public:
    PropertyInstanceString_test()
    {
    }

protected:
};

namespace {
string staticGetter()
{
    return string();
}

void staticSetter(string value)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return string();};
    auto set = [] (const string & val) {};

    auto prop = new Property<string>("stringProperty", get, set);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new Property<string>("stringProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<string>;
    auto prop = new Property<string>("stringProperty", obj, &MyObject<string>::constgetterconst, &MyObject<string>::setterconst);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<string>;
    auto prop = new Property<string>("stringProperty", obj, &MyObject<string>::getterconst, &MyObject<string>::setterconst);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<string>;
    auto prop = new Property<string>("stringProperty", obj, &MyObject<string>::getterconst, &MyObject<string>::setter);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceString_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return string();};

    auto prop = new Property<const string>("stringProperty", get);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const string>("stringProperty", &staticGetter);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<string>;
    auto prop = new Property<const string>("stringProperty", obj, &MyObject<string>::constgetterconst);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<string>;
    auto prop = new Property<const string>("stringProperty", obj, &MyObject<string>::getterconst);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceString_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<string>();
    auto prop = new Property<string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<string>(string());
    auto prop = new Property<string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return string();};
    auto set = [] (const string & val) {};
    auto accessor = new AccessorGetSet<string>(get, set);

    auto prop = new Property<string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new AccessorGetSet<string>(&staticGetter, &staticSetter);

    auto prop = new Property<string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<string>;
    auto accessor = new AccessorGetSet<string>(obj, &MyObject<string>::constgetterconst, &MyObject<string>::setterconst);
    auto prop = new Property<string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<string>;
    auto accessor = new AccessorGetSet<string>(obj, &MyObject<string>::getterconst, &MyObject<string>::setterconst);
    auto prop = new Property<string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<string>;
    auto accessor = new AccessorGetSet<string>(obj, &MyObject<string>::getterconst, &MyObject<string>::setter);
    auto prop = new Property<string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceString_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const string>();
    auto prop = new Property<const string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const string>(string());
    auto prop = new Property<string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] () {return string();};
    auto accessor = new AccessorGetSet<const string>(get);

    auto prop = new Property<const string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new AccessorGetSet<const string>(&staticGetter);

    auto prop = new Property<const string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<string>;
    auto accessor = new AccessorGetSet<const string>(obj, &MyObject<string>::constgetterconst);
    auto prop = new Property<const string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<string>;
    auto accessor = new AccessorGetSet<const string>(obj, &MyObject<string>::getterconst);
    auto prop = new Property<const string>("stringProperty", accessor);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}
