
#pragma once


#include <reflectionzeug/new/TypedUnsignedIntegral.h>


namespace reflectionzeug
{


template <typename T>
TypedUnsignedIntegral<T>::TypedUnsignedIntegral(Accessor<T> * accessor)
: TypedBase<T>(accessor)
{
}

template <typename T>
TypedUnsignedIntegral<T>::~TypedUnsignedIntegral()
{
}

template <typename T>
unsigned long long TypedUnsignedIntegral<T>::toULongLong() const
{
    return static_cast<unsigned long long>(this->get());
}

template <typename T>
bool TypedUnsignedIntegral<T>::fromULongLong(unsigned long long value)
{
    this->set(static_cast<T>(value));
    return true;
}


} // namespace reflectionzeug
