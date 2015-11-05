
#pragma once


#include <reflectionzeug/property/AccessorValue.h>


namespace reflectionzeug
{


// Read/write accessor
template <typename Type>
AccessorValue<Type>::AccessorValue()
: m_value()
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
AbstractAccessor * AccessorValue<Type>::clone() const
{
    return new AccessorValue<Type>(m_value);
}

template <typename Type>
Type * AccessorValue<Type>::ptr() const
{
    return const_cast<Type *>(&m_value);
}

template <typename Type>
Type AccessorValue<Type>::value() const
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
: m_value()
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
AbstractAccessor * AccessorValue<const Type>::clone() const
{
    return new AccessorValue<const Type>(m_value);
}

template <typename Type>
Type * AccessorValue<const Type>::ptr() const
{
    return nullptr;
}

template <typename Type>
Type AccessorValue<const Type>::value() const
{
    return m_value;
}


} // namespace reflectionzeug
