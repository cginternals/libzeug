
#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;



class PropertyInstanceBool_test : public testing::Test
{
public:
    PropertyInstanceBool_test()
    {
    }

protected:
};

namespace {
bool staticGetter()
{
    return bool();
}

void staticSetter(bool value)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return bool();};
    auto set = [] (const bool & val) {};

    auto prop = new Property<bool>("boolProperty", get, set);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new Property<bool>("boolProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new Property<bool>("boolProperty", obj, &MyObject<bool>::constgetterconst, &MyObject<bool>::setterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new Property<bool>("boolProperty", obj, &MyObject<bool>::getterconst, &MyObject<bool>::setterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<bool>;
    auto prop = new Property<bool>("boolProperty", obj, &MyObject<bool>::getterconst, &MyObject<bool>::setter);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return bool();};

    auto prop = new Property<const bool>("boolProperty", get);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const bool>("boolProperty", &staticGetter);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new Property<const bool>("boolProperty", obj, &MyObject<bool>::constgetterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new Property<const bool>("boolProperty", obj, &MyObject<bool>::getterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceBool_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<bool>();
    auto prop = new Property<bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<bool>(0);
    auto prop = new Property<bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return bool();};
    auto set = [] (const bool & val) {};
    auto accessor = new AccessorGetSet<bool>(get, set);

    auto prop = new Property<bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new AccessorGetSet<bool>(&staticGetter, &staticSetter);

    auto prop = new Property<bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new AccessorGetSet<bool>(obj, &MyObject<bool>::constgetterconst, &MyObject<bool>::setterconst);
    auto prop = new Property<bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new AccessorGetSet<bool>(obj, &MyObject<bool>::getterconst, &MyObject<bool>::setterconst);
    auto prop = new Property<bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<bool>;
    auto accessor = new AccessorGetSet<bool>(obj, &MyObject<bool>::getterconst, &MyObject<bool>::setter);
    auto prop = new Property<bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const bool>();
    auto prop = new Property<const bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const bool>(0);
    auto prop = new Property<bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] () {return bool();};
    auto accessor = new AccessorGetSet<const bool>(get);

    auto prop = new Property<const bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new AccessorGetSet<const bool>(&staticGetter);

    auto prop = new Property<const bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new AccessorGetSet<const bool>(obj, &MyObject<bool>::constgetterconst);
    auto prop = new Property<const bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new AccessorGetSet<const bool>(obj, &MyObject<bool>::getterconst);
    auto prop = new Property<const bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}
