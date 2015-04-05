
#pragma once


#include <reflectionzeug/new/TypedSignedIntegral.h>


namespace reflectionzeug
{


template <typename T>
TypedSignedIntegral<T>::TypedSignedIntegral(Accessor<T> * accessor)
: TypedBase<T>(accessor)
{
}

template <typename T>
TypedSignedIntegral<T>::~TypedSignedIntegral()
{
}

template <typename T>
long long TypedSignedIntegral<T>::toLongLong() const
{
    return static_cast<long long>(this->getValue());
}

template <typename T>
bool TypedSignedIntegral<T>::fromLongLong(long long value)
{
    this->setValue(static_cast<T>(value));
    return true;
}


} // namespace reflectionzeug
