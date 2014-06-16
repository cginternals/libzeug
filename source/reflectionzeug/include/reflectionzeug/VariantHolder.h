
#pragma once

#include <reflectionzeug/Variant2.h>
#include <reflectionzeug/VariantConverterRegistry.h>


namespace reflectionzeug
{

template <typename ValueType>
class VariantHolder : public VariantContent
{
public:
    VariantHolder(const ValueType & value)
    :   m_value(value)
    {
    }

    VariantHolder(const VariantHolder & holder)
    :   m_value(holder.m_value)
    {
    }

    virtual VariantHolder * clone() const
    {
        return new VariantHolder(*this);
    }

    virtual const std::type_info & type() const
    {
        return typeid(ValueType);
    }

    virtual bool canConvert(const std::type_info & typeInfo) const
    {
        return VariantConverterRegistry<ValueType>::instance().canConvert(typeInfo);
    }

    virtual bool convert(const std::type_info & typeInfo, void * result) const
    {
        return VariantConverterRegistry<ValueType>::instance().convert(m_value, typeInfo, result);
    }

    const ValueType & value() const
    {
        return m_value;
    }

private:
    const ValueType m_value;
};

} // namespace reflectionzeug
