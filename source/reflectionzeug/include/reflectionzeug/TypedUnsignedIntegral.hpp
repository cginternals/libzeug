
#pragma once


#include <reflectionzeug/TypedUnsignedIntegral.h>
#include <reflectionzeug/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
TypedUnsignedIntegral<T>::TypedUnsignedIntegral(Args&&... args)
: AbstractTyped<T>(std::forward<Args>(args)...)
{
}

template <typename T>
TypedUnsignedIntegral<T>::~TypedUnsignedIntegral()
{
}

template <typename T>
unsigned long long TypedUnsignedIntegral<T>::toULongLong() const
{
    return static_cast<unsigned long long>(this->getValue());
}

template <typename T>
bool TypedUnsignedIntegral<T>::fromULongLong(unsigned long long value)
{
    this->setValue(static_cast<T>(value));
    return true;
}

template <typename T>
void TypedUnsignedIntegral<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedUnsignedIntegral<T>>(this);
    visitor->callVisitor<AbstractUnsignedIntegralInterface>(this);
}


} // namespace reflectionzeug
