
#pragma once


#include <reflectionzeug/type/PropertyFloatingPoint.h>
#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyFloatingPoint<T>::PropertyFloatingPoint(Args&&... args)
: AbstractPropertyValue<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyFloatingPoint<T>::~PropertyFloatingPoint()
{
}

template <typename T>
double PropertyFloatingPoint<T>::toDouble() const
{
    return static_cast<double>(this->value());
}

template <typename T>
bool PropertyFloatingPoint<T>::fromDouble(double value)
{
    this->setValue(static_cast<T>(value));
    return true;
}

template <typename T>
void PropertyFloatingPoint<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyFloatingPoint<T>>(this);
    visitor->callVisitor<AbstractFloatingPointInterface>(this);
}


} // namespace reflectionzeug
