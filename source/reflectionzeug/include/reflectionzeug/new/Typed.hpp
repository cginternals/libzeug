
#pragma once


#include <reflectionzeug/new/Typed.h>


namespace reflectionzeug
{


template <typename Type, typename Accessor>
Typed<Type, Accessor>::Typed(const Accessor & accessor)
: TypedBase<Type, Accessor>(accessor)
{
}

template <typename Type, typename Accessor>
Typed<Type, Accessor>::~Typed()
{
}


} // namespace reflectionzeug
