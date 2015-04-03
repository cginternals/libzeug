
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


template <typename Type, typename Accessor>
TypedBase<Type, Accessor>::TypedBase(const Accessor & accessor)
: m_accessor(accessor)
{
}

template <typename Type, typename Accessor>
TypedBase<Type, Accessor>::~TypedBase()
{
}

template <typename Type, typename Accessor>
Type TypedBase<Type, Accessor>::get() const
{
    return m_accessor.get();
}

template <typename Type, typename Accessor>
void TypedBase<Type, Accessor>::set(const Type & value)
{
    m_accessor.set(value);
}


} // namespace reflectionzeug
