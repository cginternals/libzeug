
#include <gmock/gmock.h>

#include <string>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;



class PropertyInstanceDouble_test : public testing::Test
{
public:
    PropertyInstanceDouble_test()
    {
    }

protected:
};

namespace {
double staticGetter()
{
    return double();
}

void staticSetter(double value)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return double();};
    auto set = [] (const double & val) {};

    auto prop = new Property<double>("doubleProperty", get, set);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new Property<double>("doubleProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<double>;
    auto prop = new Property<double>("doubleProperty", obj, &MyObject<double>::constgetterconst, &MyObject<double>::setterconst);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<double>;
    auto prop = new Property<double>("doubleProperty", obj, &MyObject<double>::getterconst, &MyObject<double>::setterconst);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<double>;
    auto prop = new Property<double>("doubleProperty", obj, &MyObject<double>::getterconst, &MyObject<double>::setter);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceDouble_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return double();};

    auto prop = new Property<const double>("doubleProperty", get);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const double>("doubleProperty", &staticGetter);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<double>;
    auto prop = new Property<const double>("doubleProperty", obj, &MyObject<double>::constgetterconst);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<double>;
    auto prop = new Property<const double>("doubleProperty", obj, &MyObject<double>::getterconst);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceDouble_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<double>();
    auto prop = new Property<double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<double>(0);
    auto prop = new Property<double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return double();};
    auto set = [] (const double & val) {};
    auto accessor = new AccessorGetSet<double>(get, set);

    auto prop = new Property<double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new AccessorGetSet<double>(&staticGetter, &staticSetter);

    auto prop = new Property<double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<double>;
    auto accessor = new AccessorGetSet<double>(obj, &MyObject<double>::constgetterconst, &MyObject<double>::setterconst);
    auto prop = new Property<double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<double>;
    auto accessor = new AccessorGetSet<double>(obj, &MyObject<double>::getterconst, &MyObject<double>::setterconst);
    auto prop = new Property<double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<double>;
    auto accessor = new AccessorGetSet<double>(obj, &MyObject<double>::getterconst, &MyObject<double>::setter);
    auto prop = new Property<double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceDouble_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const double>();
    auto prop = new Property<const double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const double>(0);
    auto prop = new Property<double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] () {return double();};
    auto accessor = new AccessorGetSet<const double>(get);

    auto prop = new Property<const double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new AccessorGetSet<const double>(&staticGetter);

    auto prop = new Property<const double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<double>;
    auto accessor = new AccessorGetSet<const double>(obj, &MyObject<double>::constgetterconst);
    auto prop = new Property<const double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<double>;
    auto accessor = new AccessorGetSet<const double>(obj, &MyObject<double>::getterconst);
    auto prop = new Property<const double>("doubleProperty", accessor);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}
