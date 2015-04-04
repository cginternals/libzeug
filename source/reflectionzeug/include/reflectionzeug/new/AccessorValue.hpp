
#pragma once


#include <reflectionzeug/new/AccessorValue.h>


namespace reflectionzeug
{


// Read/write accessor
template <typename Type>
AccessorValue<Type>::AccessorValue()
{
}

template <typename Type>
AccessorValue<Type>::AccessorValue(const Type & defaultValue)
: m_value(defaultValue)
{
}

template <typename Type>
AccessorValue<Type>::~AccessorValue()
{
}

template <typename Type>
Type AccessorValue<Type>::get() const
{
    return m_value;
}

template <typename Type>
void AccessorValue<Type>::set(const Type & value)
{
    m_value = value;
}


// Read-only accessor
template <typename Type>
AccessorValue<const Type>::AccessorValue()
{
}

template <typename Type>
AccessorValue<const Type>::AccessorValue(const Type & defaultValue)
: m_value(defaultValue)
{
}

template <typename Type>
AccessorValue<const Type>::~AccessorValue()
{
}

template <typename Type>
Type AccessorValue<const Type>::get() const
{
    return m_value;
}


} // namespace reflectionzeug
