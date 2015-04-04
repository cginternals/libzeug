
#pragma once


#include <reflectionzeug/new/TypedUnsignedIntegral.h>


namespace reflectionzeug
{


template <typename T, typename Accessor>
TypedUnsignedIntegral<T, Accessor>::TypedUnsignedIntegral(const Accessor & accessor)
: TypedBase<T, Accessor>(accessor)
{
}

template <typename T, typename Accessor>
TypedUnsignedIntegral<T, Accessor>::~TypedUnsignedIntegral()
{
}

template <typename T, typename Accessor>
unsigned long long TypedUnsignedIntegral<T, Accessor>::toULongLong() const
{
    return static_cast<unsigned long long>(this->get());
}

template <typename T, typename Accessor>
bool TypedUnsignedIntegral<T, Accessor>::fromULongLong(unsigned long long value)
{
    this->set(static_cast<T>(value));
    return true;
}


} // namespace reflectionzeug
