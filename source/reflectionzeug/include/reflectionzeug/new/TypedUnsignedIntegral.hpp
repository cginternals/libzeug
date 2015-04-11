
#pragma once


#include <reflectionzeug/new/TypedUnsignedIntegral.h>
#include <reflectionzeug/new/AbstractVisitor.h>


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
    // Call visitor->visit(TypedUnsignedIntegral<T>)
    auto * typedVisitor = visitor->asVisitor<TypedUnsignedIntegral<T>>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }

    // Call visitor->visit(AbstractUnsignedIntegralInterface)
    auto * interfaceVisitor = visitor->asVisitor<AbstractUnsignedIntegralInterface>();
    if (interfaceVisitor) {
        interfaceVisitor->visit(this);
    }
}


} // namespace reflectionzeug
