
#pragma once


#include <reflectionzeug/Variant.h>

#include <reflectionzeug/type/Typed.h>


namespace reflectionzeug
{


template <typename ValueType>
Variant Variant::fromValue(const ValueType & value)
{
    Variant variant;
    variant.m_value = new Typed<ValueType>(new AccessorValue<ValueType>(value));
    return variant;
}

template <typename ValueType>
bool Variant::hasType() const
{
    if (!m_value)
        return false;

    return typeid(ValueType) == m_value->type();
}

template <typename ValueType>
ValueType Variant::value(const ValueType & defaultValue) const
{
    if (m_value && typeid(ValueType) == m_value->type()) {
        return static_cast<Typed<ValueType> *>(m_value)->value();
    } else {
        return defaultValue;
    }
}


} // namespace reflectionzeug
