
#include <gmock/gmock.h>

#include <string>

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


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};
    auto set = [] (const bool & val) {};

    auto prop = new Property<bool>("boolProperty", get, set);

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

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};

    auto prop = new Property<const bool>("boolProperty", get);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new Property<const bool>("boolProperty", obj, &MyObject<bool>::constgetterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_Object_GetterConst_SetterConst)
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
    auto get = [] () {return 0;};
    auto set = [] (const bool & val) {};
    auto accessor = new AccessorGetSet<bool>(get, set);

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

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};
    auto accessor = new AccessorGetSet<const bool>(get);

    auto prop = new Property<const bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new AccessorGetSet<const bool>(obj, &MyObject<bool>::constgetterconst);
    auto prop = new Property<const bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciateConstAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new AccessorGetSet<const bool>(obj, &MyObject<bool>::getterconst);
    auto prop = new Property<const bool>("boolProperty", accessor);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}
