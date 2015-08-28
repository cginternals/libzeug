
#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceUint64_T_test : public testing::Test
{
public:
    PropertyInstanceUint64_T_test()
    {
    }

protected:
};

namespace {
uint64_t staticGetter()
{
    return uint64_t();
}

void staticSetter(uint64_t value)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint64_t();};
    auto set = [] (const uint64_t & val) {};

    auto prop = new Property<uint64_t>("uint64_tProperty", get, set);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new Property<uint64_t>("uint64_tProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint64_t>;
    auto prop = new Property<uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::constgetterconst, &MyObject<uint64_t>::setterconst);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint64_t>;
    auto prop = new Property<uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::getterconst, &MyObject<uint64_t>::setterconst);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<uint64_t>;
    auto prop = new Property<uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::getterconst, &MyObject<uint64_t>::setter);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceUint64_T_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return uint64_t();};

    auto prop = new Property<const uint64_t>("uint64_tProperty", get);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const uint64_t>("uint64_tProperty", &staticGetter);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<uint64_t>;
    auto prop = new Property<const uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::constgetterconst);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<uint64_t>;
    auto prop = new Property<const uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::getterconst);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceUint64_T_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<uint64_t>();
    auto prop = new Property<uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<uint64_t>(uint64_t());
    auto prop = new Property<uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint64_t();};
    auto set = [] (const uint64_t & val) {};
    auto accessor = new AccessorGetSet<uint64_t>(get, set);

    auto prop = new Property<uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new AccessorGetSet<uint64_t>(&staticGetter, &staticSetter);

    auto prop = new Property<uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint64_t>;
    auto accessor = new AccessorGetSet<uint64_t>(obj, &MyObject<uint64_t>::constgetterconst, &MyObject<uint64_t>::setterconst);
    auto prop = new Property<uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint64_t>;
    auto accessor = new AccessorGetSet<uint64_t>(obj, &MyObject<uint64_t>::getterconst, &MyObject<uint64_t>::setterconst);
    auto prop = new Property<uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<uint64_t>;
    auto accessor = new AccessorGetSet<uint64_t>(obj, &MyObject<uint64_t>::getterconst, &MyObject<uint64_t>::setter);
    auto prop = new Property<uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceUint64_T_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const uint64_t>();
    auto prop = new Property<const uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const uint64_t>(uint64_t());
    auto prop = new Property<uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] () {return uint64_t();};
    auto accessor = new AccessorGetSet<const uint64_t>(get);

    auto prop = new Property<const uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new AccessorGetSet<const uint64_t>(&staticGetter);

    auto prop = new Property<const uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<uint64_t>;
    auto accessor = new AccessorGetSet<const uint64_t>(obj, &MyObject<uint64_t>::constgetterconst);
    auto prop = new Property<const uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<uint64_t>;
    auto accessor = new AccessorGetSet<const uint64_t>(obj, &MyObject<uint64_t>::getterconst);
    auto prop = new Property<const uint64_t>("uint64_tProperty", accessor);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}
