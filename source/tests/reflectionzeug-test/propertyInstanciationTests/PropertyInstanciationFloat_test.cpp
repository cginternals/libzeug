
#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceFloat_test : public testing::Test
{
public:
    PropertyInstanceFloat_test()
    {
    }

protected:
};

namespace {
float staticGetter()
{
    return float();
}

void staticSetter(float /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return float();};
    auto set = [] (const float & /*val*/) {};

    auto prop = new Property<float>("floatProperty", get, set);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new Property<float>("floatProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<float>;
    auto prop = new Property<float>("floatProperty", obj, &MyObject<float>::constgetterconst, &MyObject<float>::setterconst);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<float>;
    auto prop = new Property<float>("floatProperty", obj, &MyObject<float>::getterconst, &MyObject<float>::setterconst);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<float>;
    auto prop = new Property<float>("floatProperty", obj, &MyObject<float>::getterconst, &MyObject<float>::setter);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceFloat_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return float();};

    auto prop = new Property<const float>("floatProperty", get);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const float>("floatProperty", &staticGetter);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<float>;
    auto prop = new Property<const float>("floatProperty", obj, &MyObject<float>::constgetterconst);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<float>;
    auto prop = new Property<const float>("floatProperty", obj, &MyObject<float>::getterconst);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceFloat_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<float>();
    auto prop = new Property<float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<float>(float());
    auto prop = new Property<float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return float();};
    auto set = [] (const float & /*val*/) {};
    auto accessor = new AccessorGetSet<float>(get, set);

    auto prop = new Property<float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new AccessorGetSet<float>(&staticGetter, &staticSetter);

    auto prop = new Property<float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<float>;
    auto accessor = new AccessorGetSet<float>(obj, &MyObject<float>::constgetterconst, &MyObject<float>::setterconst);
    auto prop = new Property<float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<float>;
    auto accessor = new AccessorGetSet<float>(obj, &MyObject<float>::getterconst, &MyObject<float>::setterconst);
    auto prop = new Property<float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<float>;
    auto accessor = new AccessorGetSet<float>(obj, &MyObject<float>::getterconst, &MyObject<float>::setter);
    auto prop = new Property<float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceFloat_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const float>();
    auto prop = new Property<const float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const float>(float());
    auto prop = new Property<float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] () {return float();};
    auto accessor = new AccessorGetSet<const float>(get);

    auto prop = new Property<const float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new AccessorGetSet<const float>(&staticGetter);

    auto prop = new Property<const float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<float>;
    auto accessor = new AccessorGetSet<const float>(obj, &MyObject<float>::constgetterconst);
    auto prop = new Property<const float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<float>;
    auto accessor = new AccessorGetSet<const float>(obj, &MyObject<float>::getterconst);
    auto prop = new Property<const float>("floatProperty", accessor);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}
