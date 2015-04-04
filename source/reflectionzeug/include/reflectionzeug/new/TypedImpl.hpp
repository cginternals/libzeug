
#pragma once


#include <reflectionzeug/new/TypedImpl.h>


namespace reflectionzeug
{


template <typename Type, typename Accessor>
TypedImpl<Type, Accessor>::TypedImpl(const Accessor & accessor)
: TypedBase<Type, Accessor>(accessor)
{
}

template <typename Type, typename Accessor>
TypedImpl<Type, Accessor>::~TypedImpl()
{
}


} // namespace reflectionzeug
