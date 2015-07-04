
#include <gmock/gmock.h>

#include <string>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;



class PropertyInstanceUint16_T_test : public testing::Test
{
public:
    PropertyInstanceUint16_T_test()
    {
    }

protected:
};


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};
    auto set = [] (const uint16_t & val) {};

    auto prop = new Property<uint16_t>("uint16_tProperty", get, set);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>;
    auto prop = new Property<uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::constgetterconst, &MyObject<uint16_t>::setterconst);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>;
    auto prop = new Property<uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::getterconst, &MyObject<uint16_t>::setterconst);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<uint16_t>;
    auto prop = new Property<uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::getterconst, &MyObject<uint16_t>::setter);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceUint16_T_test, instanciateConstPropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};

    auto prop = new Property<const uint16_t>("uint16_tProperty", get);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>;
    auto prop = new Property<const uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::constgetterconst);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateConstPropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>;
    auto prop = new Property<const uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::getterconst);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceUint16_T_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<uint16_t>();
    auto prop = new Property<uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<uint16_t>(0);
    auto prop = new Property<uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};
    auto set = [] (const uint16_t & val) {};
    auto accessor = new AccessorGetSet<uint16_t>(get, set);

    auto prop = new Property<uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>;
    auto accessor = new AccessorGetSet<uint16_t>(obj, &MyObject<uint16_t>::constgetterconst, &MyObject<uint16_t>::setterconst);
    auto prop = new Property<uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>;
    auto accessor = new AccessorGetSet<uint16_t>(obj, &MyObject<uint16_t>::getterconst, &MyObject<uint16_t>::setterconst);
    auto prop = new Property<uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<uint16_t>;
    auto accessor = new AccessorGetSet<uint16_t>(obj, &MyObject<uint16_t>::getterconst, &MyObject<uint16_t>::setter);
    auto prop = new Property<uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceUint16_T_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const uint16_t>();
    auto prop = new Property<const uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const uint16_t>(0);
    auto prop = new Property<uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateConstAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};
    auto accessor = new AccessorGetSet<const uint16_t>(get);

    auto prop = new Property<const uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateConstAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>;
    auto accessor = new AccessorGetSet<const uint16_t>(obj, &MyObject<uint16_t>::constgetterconst);
    auto prop = new Property<const uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateConstAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>;
    auto accessor = new AccessorGetSet<const uint16_t>(obj, &MyObject<uint16_t>::getterconst);
    auto prop = new Property<const uint16_t>("uint16_tProperty", accessor);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}