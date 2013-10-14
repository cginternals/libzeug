
#pragma once

namespace zeug 
{

template <typename Type>
StoredValue<Type>::StoredValue(const Type & value)
:   m_value(value)
{   
}

template <typename Type>
StoredValue<Type>::~StoredValue()
{
}

template <typename Type>
Type StoredValue<Type>::get() const
{
    return m_value;
}

template <typename Type>
void StoredValue<Type>::set(const Type & value)
{
    m_value = value;
}

} // namespace
