
#pragma once

#include <reflectionzeug/Variant.h>


namespace reflectionzeug
{

class REFLECTIONZEUG_API VariantContent
{
public:
    virtual ~VariantContent() = default;
    virtual VariantContent * clone() const = 0;

    virtual const std::type_info & type() const = 0;

    virtual bool canConvert(const std::type_info & typeInfo) const = 0;
    virtual bool convert(const std::type_info & typeInfo, void * result) const = 0;
};

template <typename ValueType>
class VariantHolder : public VariantContent
{
public:
    VariantHolder(const ValueType & value);
    VariantHolder(ValueType && value);
    VariantHolder(const VariantHolder & holder);

    virtual VariantHolder * clone() const;

    virtual const std::type_info & type() const;

    virtual bool canConvert(const std::type_info & typeInfo) const;

    virtual bool convert(const std::type_info & typeInfo, void * result) const;

    const ValueType & value() const;

    ValueType * ptr();

private:
    const ValueType m_value;
};

} // namespace reflectionzeug

#include "VariantHolder.hpp"
