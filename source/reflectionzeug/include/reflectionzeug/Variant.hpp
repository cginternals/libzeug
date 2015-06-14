
#pragma once


#include <reflectionzeug/Variant.h>

#include <reflectionzeug/type/AccessorValue.h>


namespace reflectionzeug
{


template <typename ValueType>
Variant Variant::fromValue(const ValueType & value)
{
    Variant variant;
    variant.m_accessor = new AccessorValue<ValueType>(value);
    return variant;
}

template <typename ValueType>
bool Variant::hasType() const
{
    if (!m_accessor) {
        return false;
    }

    return typeid(ValueType) == m_accessor->type();
}

template <typename ValueType>
ValueType Variant::value(const ValueType & defaultValue) const
{
    if (m_accessor && typeid(ValueType) == m_accessor->type()) {
        return static_cast<AccessorValue<ValueType> *>(m_accessor)->value();
    } else {
        return defaultValue;
    }
}

template <typename ValueType>
ValueType * Variant::ptr()
{
    if (m_accessor && typeid(ValueType) == m_accessor->type()) {
        return static_cast<AccessorValue<ValueType> *>(m_accessor)->ptr();
    } else {
        return nullptr;
    }
}

template <typename ValueType>
const ValueType * Variant::ptr() const
{
    if (m_accessor && typeid(ValueType) == m_accessor->type()) {
        return static_cast<const AccessorValue<ValueType> *>(m_accessor)->ptr();
    } else {
        return nullptr;
    }
}


} // namespace reflectionzeug
