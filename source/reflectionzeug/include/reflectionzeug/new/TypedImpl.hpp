
#pragma once


#include <reflectionzeug/new/TypedImpl.h>


namespace reflectionzeug
{


template <typename T, typename Accessor>
TypedImpl<T, Accessor>::TypedImpl(const Accessor & accessor)
: TypeSelector<T, Accessor>::Type(accessor)
{
}

template <typename T, typename Accessor>
TypedImpl<T, Accessor>::~TypedImpl()
{
}


} // namespace reflectionzeug
