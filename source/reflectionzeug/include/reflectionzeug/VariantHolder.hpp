
#pragma once

#include <reflectionzeug/VariantHolder.h>

#include <reflectionzeug/VariantConverterRegistry.h>


namespace reflectionzeug
{

template <typename ValueType>
VariantHolder<ValueType>::VariantHolder(const ValueType & value)
:   m_value(value)
{
}

template <typename ValueType>
VariantHolder<ValueType>::VariantHolder(ValueType && value)
:   m_value(std::move(value))
{
}

template <typename ValueType>
VariantHolder<ValueType>::VariantHolder(const VariantHolder & holder)
:   m_value(holder.m_value)
{
}

template <typename ValueType>
VariantHolder<ValueType> * VariantHolder<ValueType>::clone() const
{
    return new VariantHolder(*this);
}

template <typename ValueType>
const std::type_info & VariantHolder<ValueType>::type() const
{
    return typeid(ValueType);
}

template <typename ValueType>
bool VariantHolder<ValueType>::canConvert(const std::type_info & typeInfo) const
{
    return VariantConverterRegistry<ValueType>::instance().canConvert(typeInfo);
}

template <typename ValueType>
bool VariantHolder<ValueType>::convert(const std::type_info & typeInfo, void * result) const
{
    return VariantConverterRegistry<ValueType>::instance().convert(m_value, typeInfo, result);
}

template <typename ValueType>
const ValueType & VariantHolder<ValueType>::value() const
{
    return m_value;
}

template <typename ValueType>
ValueType * VariantHolder<ValueType>::ptr()
{
    return &m_value;
}

} // namespace reflectionzeug
