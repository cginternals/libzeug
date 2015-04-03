
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
template<class P1, class P2>
Typed<int, Accessor>::Typed(P1 && arg1, P2 && arg2)
: TypedBase<int, Accessor>(Accessor(arg1, arg2))
{
}

template <typename Accessor>
template<class P1>
Typed<int, Accessor>::Typed(P1 && arg1)
: TypedBase<int, Accessor>(Accessor(arg1))
{
}

template <typename Accessor>
Typed<int, Accessor>::~Typed()
{
}


} // namespace reflectionzeug
