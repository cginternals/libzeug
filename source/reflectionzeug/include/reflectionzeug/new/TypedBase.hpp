
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


} // namespace reflectionzeug
