
#pragma once


#include <reflectionzeug/property/PropertyUnsignedIntegral.h>
#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyUnsignedIntegral<T>::PropertyUnsignedIntegral(Args&&... args)
: AbstractNumberProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyUnsignedIntegral<T>::~PropertyUnsignedIntegral()
{
}

template <typename T>
unsigned long long PropertyUnsignedIntegral<T>::toULongLong() const
{
    return static_cast<unsigned long long>(this->value());
}

template <typename T>
bool PropertyUnsignedIntegral<T>::fromULongLong(unsigned long long value)
{
    this->setValue(static_cast<T>(value));
    return true;
}

template <typename T>
void PropertyUnsignedIntegral<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyUnsignedIntegral<T>>(this);
    visitor->callVisitor<AbstractUnsignedIntegralInterface>(this);
}

template <typename T>
std::string PropertyUnsignedIntegral<T>::matchRegex() const
{
    // Match an integral number
    return "\\+?\\d+";
}


} // namespace reflectionzeug
