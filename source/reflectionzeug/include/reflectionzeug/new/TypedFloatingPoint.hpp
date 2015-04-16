
#pragma once


#include <reflectionzeug/new/TypedFloatingPoint.h>
#include <reflectionzeug/new/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
TypedFloatingPoint<T>::TypedFloatingPoint(Args&&... args)
: AbstractTyped<T>(std::forward<Args>(args)...)
{
}

template <typename T>
TypedFloatingPoint<T>::~TypedFloatingPoint()
{
}

template <typename T>
double TypedFloatingPoint<T>::toDouble() const
{
    return static_cast<double>(this->getValue());
}

template <typename T>
bool TypedFloatingPoint<T>::fromDouble(double value)
{
    this->setValue(static_cast<T>(value));
    return true;
}

template <typename T>
void TypedFloatingPoint<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedFloatingPoint<T>>(this);
    visitor->callVisitor<AbstractFloatingPointInterface>(this);
}


} // namespace reflectionzeug