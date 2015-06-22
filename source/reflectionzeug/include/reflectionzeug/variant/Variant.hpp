
#pragma once


#include <reflectionzeug/variant/Variant.h>

#include <reflectionzeug/property/AccessorValue.h>


namespace
{


template <typename ValueType>
struct ConvertTo
{
    static ValueType convertTo(const reflectionzeug::Variant & variant) {
        return ValueType();
    }
};

template <>
struct ConvertTo<std::string>
{
    static std::string convertTo(const reflectionzeug::Variant & variant) {
        return variant.toJSON();
    }
};


} // namespace


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
bool Variant::canConvert() const
{
    return m_accessor->canConvert(typeid(ValueType));
}

template <typename ValueType>
ValueType Variant::value(const ValueType & defaultValue) const
{
    // Type of variant is the wanted type
    if (m_accessor && typeid(ValueType) == m_accessor->type()) {
        return static_cast<AccessorValue<ValueType> *>(m_accessor)->value();
    }

    // Variant has to be converted
    else if (m_accessor && m_accessor->canConvert(typeid(ValueType))) {
        // Try to convert value
        ValueType converted;
        if (m_accessor->convert(static_cast<void*>(&converted), typeid(ValueType))) {
            return converted;
        }
    }

    // Variant map or array to string conversion
    else if (isMap() || isArray()) {
        return ConvertTo<ValueType>::convertTo(*this);
    }

    // No conversion possible
    return defaultValue;
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
