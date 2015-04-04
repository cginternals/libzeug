
#pragma once


#include <reflectionzeug/new/TypedSignedIntegral.h>


namespace reflectionzeug
{


template <typename T, typename Accessor>
TypedSignedIntegral<T, Accessor>::TypedSignedIntegral(const Accessor & accessor)
: TypedBase<T, Accessor>(accessor)
{
}

template <typename T, typename Accessor>
TypedSignedIntegral<T, Accessor>::~TypedSignedIntegral()
{
}

template <typename T, typename Accessor>
long long TypedSignedIntegral<T, Accessor>::toLongLong() const
{
    return static_cast<long long>(this->get());
}

template <typename T, typename Accessor>
bool TypedSignedIntegral<T, Accessor>::fromLongLong(long long value)
{
    this->set(static_cast<T>(value));
    return true;
}


} // namespace reflectionzeug
