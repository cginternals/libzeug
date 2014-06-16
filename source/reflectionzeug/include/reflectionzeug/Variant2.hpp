
#pragma once

#include <cassert>

#include <reflectionzeug/TypeId.h>
#include <reflectionzeug/VariantHolder.h>


namespace reflectionzeug
{

template <typename ValueType>
Variant2 Variant2::fromValue(const ValueType & value)
{
    return Variant2(value);
}

template <typename ValueType>
Variant2::Variant2(const ValueType & value)
:   m_content(new VariantHolder<ValueType>(value))
{
}

template <typename ValueType>
const ValueType & Variant2::to() const
{
    assert(m_content);
    assert(typeid(ValueType) == m_content->type());
    return static_cast<VariantHolder<ValueType> *>(m_content.get())->value();
}

template <typename ValueType>
bool Variant2::canConvert() const
{
    if (!m_content)
        return false;

    return m_content->canConvert(typeid(ValueType));
}

template <typename ValueType>
bool Variant2::convert()
{
    if (!m_content)
        return false;

    ValueType value;
    
    bool ok = m_content->convert(typeid(ValueType), &value);

    if (!ok)
        return false;
    
    m_content.reset(new VariantHolder<ValueType>(value));

    return true;
}

} // namespace reflectionzeug
