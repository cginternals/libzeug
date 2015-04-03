
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
template<class P1, class P2>
Typed<Type, Accessor>::Typed(P1 && arg1, P2 && arg2)
: TypedBase<Type, Accessor>(Accessor(arg1, arg2))
{
}

template <typename Type, typename Accessor>
template<class P1>
Typed<Type, Accessor>::Typed(P1 && arg1)
: TypedBase<Type, Accessor>(Accessor(arg1))
{
}

template <typename Type, typename Accessor>
Typed<Type, Accessor>::~Typed()
{
}


} // namespace reflectionzeug
