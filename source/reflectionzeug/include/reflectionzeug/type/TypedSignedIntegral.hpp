
#pragma once


#include <reflectionzeug/type/TypedSignedIntegral.h>
#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
TypedSignedIntegral<T>::TypedSignedIntegral(Args&&... args)
: AbstractTyped<T>(std::forward<Args>(args)...)
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

template <typename T>
void TypedSignedIntegral<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedSignedIntegral<T>>(this);
    visitor->callVisitor<AbstractSignedIntegralInterface>(this);
}


} // namespace reflectionzeug
