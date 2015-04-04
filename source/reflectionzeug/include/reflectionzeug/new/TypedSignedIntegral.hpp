
#pragma once


#include <reflectionzeug/new/TypedSignedIntegral.h>


namespace reflectionzeug
{


template <typename T, typename Accessor>
TypedSignedIntegral<T, Accessor>::TypedSignedIntegral(const Accessor & accessor)
: TypedBase<int, Accessor>(accessor)
{
}

template <typename T, typename Accessor>
TypedSignedIntegral<T, Accessor>::~TypedSignedIntegral()
{
}

template <typename T, typename Accessor>
void TypedSignedIntegral<T, Accessor>::isInteger()
{
}


} // namespace reflectionzeug
