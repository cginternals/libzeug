#include "MyObject.h"


using namespace reflectionzeug;

MyObject::MyObject()
:   Object(std::string("my_object"))
, m_intValue{-13}
, m_enumValue{MyEnum::Value1}
, m_floatArray({{ 0.5f, 1.0f, 0.3f }})
, m_boolValue{true}
{
    // Register properties with accessors ...
    addProperty<int>(
        "int_value", this,
        &MyObject::intValue,
        &MyObject::setIntValue);

    addProperty<MyEnum>(
        "enum_value", this,
        &MyObject::enumValue,
        &MyObject::setEnumValue);

    // Array properties have different accessor interfaces
    addProperty<std::array<float, 3>>(
        "float_array", this,
        &MyObject::floatArrayAt,
        &MyObject::setFloatArrayAt);

    // Because `PropertyGroup` inherits from `AbstractProperty` as well,
    // you can nest them and thus create hierarchies.
    auto subGroup = addGroup("sub_group");

    // Create your property elsewhere, e.g., via lambdas.
    auto boolProperty = new Property<bool>("bool_value",
        [this]() { return m_boolValue; },
        [this](bool value) { m_boolValue = value; });

    subGroup->addProperty(boolProperty);
}

int MyObject::intValue() const
{
    return m_intValue;
}

void MyObject::setIntValue(const int & value)
{
    m_intValue = value;
}

MyEnum MyObject::enumValue() const
{
    return m_enumValue;
}

void MyObject::setEnumValue(MyEnum value)
{
    m_enumValue = value;
}

float MyObject::floatArrayAt(size_t i) const
{
    return m_floatArray.at(i);
}

void MyObject::setFloatArrayAt(size_t i, float value)
{
    m_floatArray.at(i) = value;
}
