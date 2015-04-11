
#pragma once


#include <reflectionzeug/new/TypedSignedIntegral.h>
#include <reflectionzeug/new/AbstractVisitor.h>


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
    // Call visitor->visit(TypedSignedIntegral<T>)
    auto * typedVisitor = visitor->asVisitor<TypedSignedIntegral<T>>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }

    // Call visitor->visit(AbstractSignedIntegralInterface)
    auto * interfaceVisitor = visitor->asVisitor<AbstractSignedIntegralInterface>();
    if (interfaceVisitor) {
        interfaceVisitor->visit(this);
    }
}


} // namespace reflectionzeug
