
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
template <typename... Args>
Typed<Type, Accessor>::Typed(Args&&... args)
: TypedImpl<Type, Accessor>(Accessor(std::forward<Args>(args)...))
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
template <typename... Args>
Typed<const Type, Accessor>::Typed(Args&&... args)
: TypedImpl<Type, Accessor>(Accessor(std::forward<Args>(args)...))
{
}

template <typename Type, typename Accessor>
Typed<const Type, Accessor>::~Typed()
{
}


} // namespace reflectionzeug
