
#include <gmock/gmock.h>

#include <string>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;



class PropertyInstanceInt32_T_test : public testing::Test
{
public:
    PropertyInstanceInt32_T_test()
    {
    }

protected:
};

namespace {
int32_t staticGetter()
{
    return int32_t();
}

void staticSetter(int32_t value)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt32_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int32_t();};
    auto set = [] (const int32_t & val) {};

    auto prop = new Property<int32_t>("int32_tProperty", get, set);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new Property<int32_t>("int32_tProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<int32_t>;
    auto prop = new Property<int32_t>("int32_tProperty", obj, &MyObject<int32_t>::constgetterconst, &MyObject<int32_t>::setterconst);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt32_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<int32_t>;
    auto prop = new Property<int32_t>("int32_tProperty", obj, &MyObject<int32_t>::getterconst, &MyObject<int32_t>::setterconst);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt32_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<int32_t>;
    auto prop = new Property<int32_t>("int32_tProperty", obj, &MyObject<int32_t>::getterconst, &MyObject<int32_t>::setter);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceInt32_T_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return int32_t();};

    auto prop = new Property<const int32_t>("int32_tProperty", get);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const int32_t>("int32_tProperty", &staticGetter);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<int32_t>;
    auto prop = new Property<const int32_t>("int32_tProperty", obj, &MyObject<int32_t>::constgetterconst);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<int32_t>;
    auto prop = new Property<const int32_t>("int32_tProperty", obj, &MyObject<int32_t>::getterconst);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceInt32_T_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<int32_t>();
    auto prop = new Property<int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<int32_t>(0);
    auto prop = new Property<int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int32_t();};
    auto set = [] (const int32_t & val) {};
    auto accessor = new AccessorGetSet<int32_t>(get, set);

    auto prop = new Property<int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new AccessorGetSet<int32_t>(&staticGetter, &staticSetter);

    auto prop = new Property<int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<int32_t>;
    auto accessor = new AccessorGetSet<int32_t>(obj, &MyObject<int32_t>::constgetterconst, &MyObject<int32_t>::setterconst);
    auto prop = new Property<int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<int32_t>;
    auto accessor = new AccessorGetSet<int32_t>(obj, &MyObject<int32_t>::getterconst, &MyObject<int32_t>::setterconst);
    auto prop = new Property<int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<int32_t>;
    auto accessor = new AccessorGetSet<int32_t>(obj, &MyObject<int32_t>::getterconst, &MyObject<int32_t>::setter);
    auto prop = new Property<int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceInt32_T_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const int32_t>();
    auto prop = new Property<const int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const int32_t>(0);
    auto prop = new Property<int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] () {return int32_t();};
    auto accessor = new AccessorGetSet<const int32_t>(get);

    auto prop = new Property<const int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new AccessorGetSet<const int32_t>(&staticGetter);

    auto prop = new Property<const int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<int32_t>;
    auto accessor = new AccessorGetSet<const int32_t>(obj, &MyObject<int32_t>::constgetterconst);
    auto prop = new Property<const int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt32_T_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<int32_t>;
    auto accessor = new AccessorGetSet<const int32_t>(obj, &MyObject<int32_t>::getterconst);
    auto prop = new Property<const int32_t>("int32_tProperty", accessor);

    ASSERT_EQ(typeid(int32_t), prop->type());


    delete prop;
    delete obj;
}
