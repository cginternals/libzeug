
#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceVariant_test : public testing::Test
{
public:
    PropertyInstanceVariant_test()
    {
    }

protected:
};

namespace {
Variant staticGetter()
{
    return Variant();
}

void staticSetter(Variant /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return Variant();};
    auto set = [] (const Variant & /*val*/) {};

    auto prop = new Property<Variant>("VariantProperty", get, set);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new Property<Variant>("VariantProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>;
    auto prop = new Property<Variant>("VariantProperty", obj, &MyObject<Variant>::constgetterconst, &MyObject<Variant>::setterconst);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>;
    auto prop = new Property<Variant>("VariantProperty", obj, &MyObject<Variant>::getterconst, &MyObject<Variant>::setterconst);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<Variant>;
    auto prop = new Property<Variant>("VariantProperty", obj, &MyObject<Variant>::getterconst, &MyObject<Variant>::setter);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceVariant_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return Variant();};

    auto prop = new Property<const Variant>("VariantProperty", get);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const Variant>("VariantProperty", &staticGetter);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<Variant>;
    auto prop = new Property<const Variant>("VariantProperty", obj, &MyObject<Variant>::constgetterconst);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<Variant>;
    auto prop = new Property<const Variant>("VariantProperty", obj, &MyObject<Variant>::getterconst);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceVariant_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<Variant>();
    auto prop = new Property<Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<Variant>(Variant());
    auto prop = new Property<Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return Variant();};
    auto set = [] (const Variant & /*val*/) {};
    auto accessor = new AccessorGetSet<Variant>(get, set);

    auto prop = new Property<Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new AccessorGetSet<Variant>(&staticGetter, &staticSetter);

    auto prop = new Property<Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new AccessorGetSet<Variant>(obj, &MyObject<Variant>::constgetterconst, &MyObject<Variant>::setterconst);
    auto prop = new Property<Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new AccessorGetSet<Variant>(obj, &MyObject<Variant>::getterconst, &MyObject<Variant>::setterconst);
    auto prop = new Property<Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new AccessorGetSet<Variant>(obj, &MyObject<Variant>::getterconst, &MyObject<Variant>::setter);
    auto prop = new Property<Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceVariant_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const Variant>();
    auto prop = new Property<const Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const Variant>(Variant());
    auto prop = new Property<Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] () {return Variant();};
    auto accessor = new AccessorGetSet<const Variant>(get);

    auto prop = new Property<const Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new AccessorGetSet<const Variant>(&staticGetter);

    auto prop = new Property<const Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new AccessorGetSet<const Variant>(obj, &MyObject<Variant>::constgetterconst);
    auto prop = new Property<const Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new AccessorGetSet<const Variant>(obj, &MyObject<Variant>::getterconst);
    auto prop = new Property<const Variant>("VariantProperty", accessor);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}
