
#pragma once


#include <reflectionzeug/new/TypedInt.h>


namespace reflectionzeug
{


template <typename Accessor>
Typed<int, Accessor>::Typed(const Accessor & accessor)
: TypedBase<int, Accessor>(accessor)
{
}

template <typename Accessor>
Typed<int, Accessor>::~Typed()
{
}


} // namespace reflectionzeug
