
#pragma once


#include <reflectionzeug/new/Variant.h>


namespace reflectionzeug
{


template <typename ValueType>
Variant2 Variant2::fromValue(const ValueType & value)
{
    Variant2 variant;
    variant.m_value = new Typed<ValueType>(new AccessorValue<ValueType>(value));
    return variant;
}

template <typename ValueType>
bool Variant2::hasType() const
{
    if (!m_value)
        return false;

    return typeid(ValueType) == m_value->type();
}

template <typename ValueType>
ValueType Variant2::value(const ValueType & defaultValue) const
{
    if (m_value && typeid(ValueType) == m_value->type()) {
        return static_cast<Typed<ValueType> *>(m_value)->value();
    } else {
        return defaultValue;
    }
}


} // namespace reflectionzeug
