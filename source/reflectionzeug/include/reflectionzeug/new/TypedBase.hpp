
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
Type TypedBase<Type>::get() const
{
    return m_accessor->get();
}

template <typename Type>
void TypedBase<Type>::set(const Type & value)
{
    m_accessor->set(value);
}


} // namespace reflectionzeug
