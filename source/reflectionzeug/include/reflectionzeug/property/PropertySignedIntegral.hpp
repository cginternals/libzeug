
#pragma once


#include <reflectionzeug/property/PropertySignedIntegral.h>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertySignedIntegral<T>::PropertySignedIntegral(Args&&... args)
: AbstractNumberProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertySignedIntegral<T>::~PropertySignedIntegral()
{
}

template <typename T>
long long PropertySignedIntegral<T>::toLongLong() const
{
    return static_cast<long long>(this->value());
}

template <typename T>
bool PropertySignedIntegral<T>::fromLongLong(long long value)
{
    this->setValue(static_cast<T>(value));
    return true;
}

template <typename T>
void PropertySignedIntegral<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertySignedIntegral<T>>(this);
    visitor->callVisitor<AbstractSignedIntegralInterface>(this);
}

template <typename T>
std::string PropertySignedIntegral<T>::matchRegex() const
{
    // Match an integral number
    return "(-|\\+)?\\d+";
}


} // namespace reflectionzeug
