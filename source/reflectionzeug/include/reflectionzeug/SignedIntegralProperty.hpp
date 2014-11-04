#pragma once

#include <reflectionzeug/SignedIntegralProperty.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
SignedIntegralProperty<Type>::SignedIntegralProperty(Arguments&&... args)
:   NumberProperty<Type, SignedIntegralPropertyInterface>(std::forward<Arguments>(args)...)
{
}
    
template <typename Type>
SignedIntegralProperty<Type>::~SignedIntegralProperty()
{
}

template <typename Type>
void SignedIntegralProperty<Type>::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);
    
    if (typedVisitor == nullptr)
        return SignedIntegralPropertyInterface::accept(visitor);
    
    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

template <typename Type>
long long SignedIntegralProperty<Type>::toLongLong() const
{
    return this->value();
}

template <typename Type>
bool SignedIntegralProperty<Type>::fromLongLong(long long integral)
{
    this->setValue(static_cast<Type>(integral));
    return true;
}

template <typename Type>
std::string SignedIntegralProperty<Type>::matchRegex() const
{
    return "(-|\\+)?\\d+";
}

} // namespace reflectionzeug
