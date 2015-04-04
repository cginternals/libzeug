
#pragma once


#include <reflectionzeug/new/TypedImplInt.h>


namespace reflectionzeug
{


template <typename Accessor>
TypedImpl<int, Accessor>::TypedImpl(const Accessor & accessor)
: TypedBase<int, Accessor>(accessor)
{
}

template <typename Accessor>
TypedImpl<int, Accessor>::~TypedImpl()
{
}


} // namespace reflectionzeug
