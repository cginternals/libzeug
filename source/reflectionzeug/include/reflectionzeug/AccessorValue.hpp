
#pragma once


#include <reflectionzeug/AccessorValue.h>


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
Type AccessorValue<Type>::getValue() const
{
    return m_value;
}

template <typename Type>
void AccessorValue<Type>::setValue(const Type & value)
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
Type AccessorValue<const Type>::getValue() const
{
    return m_value;
}


} // namespace reflectionzeug
