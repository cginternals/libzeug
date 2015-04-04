
#pragma once


#include <reflectionzeug/new/Typed.h>


namespace reflectionzeug
{


// Read/write value
template <typename Type, typename Accessor>
Typed<Type, Accessor>::Typed(const Accessor & accessor)
: TypedImpl<Type, Accessor>(accessor)
{
}

template <typename Type, typename Accessor>
template<class Arg1, class Arg2, class Arg3>
Typed<Type, Accessor>::Typed(Arg1 && arg1, Arg2 && arg2, Arg3 && arg3)
: TypedImpl<Type, Accessor>(Accessor(arg1, arg2, arg3))
{
}

template <typename Type, typename Accessor>
template<class Arg1, class Arg2>
Typed<Type, Accessor>::Typed(Arg1 && arg1, Arg2 && arg2)
: TypedImpl<Type, Accessor>(Accessor(arg1, arg2))
{
}

template <typename Type, typename Accessor>
template<class Arg1>
Typed<Type, Accessor>::Typed(Arg1 && arg1)
: TypedImpl<Type, Accessor>(Accessor(arg1))
{
}

template <typename Type, typename Accessor>
Typed<Type, Accessor>::~Typed()
{
}


// Read-only value
template <typename Type, typename Accessor>
Typed<const Type, Accessor>::Typed(const Accessor & accessor)
: TypedImpl<Type, Accessor>(accessor)
{
}

template <typename Type, typename Accessor>
template<class Arg1, class Arg2, class Arg3>
Typed<const Type, Accessor>::Typed(Arg1 && arg1, Arg2 && arg2, Arg3 && arg3)
: TypedImpl<Type, Accessor>(Accessor(arg1, arg2, arg3))
{
}

template <typename Type, typename Accessor>
template<class Arg1, class Arg2>
Typed<const Type, Accessor>::Typed(Arg1 && arg1, Arg2 && arg2)
: TypedImpl<Type, Accessor>(Accessor(arg1, arg2))
{
}

template <typename Type, typename Accessor>
template<class Arg1>
Typed<const Type, Accessor>::Typed(Arg1 && arg1)
: TypedImpl<Type, Accessor>(Accessor(arg1))
{
}

template <typename Type, typename Accessor>
Typed<const Type, Accessor>::~Typed()
{
}


} // namespace reflectionzeug
