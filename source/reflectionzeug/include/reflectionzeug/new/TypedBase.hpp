
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


template <typename Type>
TypedBase<Type>::TypedBase(Accessor<Type> * accessor)
: m_accessor(accessor)
{
}

template <typename Type>
TypedBase<Type>::~TypedBase()
{
}

template <typename Type>
Type TypedBase<Type>::getValue() const
{
    return m_accessor->getValue();
}

template <typename Type>
void TypedBase<Type>::setValue(const Type & value)
{
    m_accessor->setValue(value);
}


} // namespace reflectionzeug
