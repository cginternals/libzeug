
#pragma once


#include <reflectionzeug/new/TypedFloatingPoint.h>


namespace reflectionzeug
{


template <typename T, typename Accessor>
TypedFloatingPoint<T, Accessor>::TypedFloatingPoint(const Accessor & accessor)
: TypedBase<T, Accessor>(accessor)
{
}

template <typename T, typename Accessor>
TypedFloatingPoint<T, Accessor>::~TypedFloatingPoint()
{
}

template <typename T, typename Accessor>
double TypedFloatingPoint<T, Accessor>::toDouble() const
{
    return static_cast<double>(this->get());
}

template <typename T, typename Accessor>
bool TypedFloatingPoint<T, Accessor>::fromDouble(double value)
{
    this->set(static_cast<T>(value));
    return true;
}


} // namespace reflectionzeug
