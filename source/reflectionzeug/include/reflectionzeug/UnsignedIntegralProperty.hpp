#pragma once

#include <reflectionzeug/UnsignedIntegralProperty.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
UnsignedIntegralProperty<Type>::UnsignedIntegralProperty(Arguments&&... args)
:   NumberProperty<Type>(std::forward<Arguments>(args)...)
{
}
    
template <typename Type>
UnsignedIntegralProperty<Type>::~UnsignedIntegralProperty()
{
}

template <typename Type>
void UnsignedIntegralProperty<Type>::accept(AbstractPropertyVisitor * visitor)
{
    UnsignedIntegralPropertyInterface::accept(visitor);
}

template <typename Type>
unsigned long long UnsignedIntegralProperty<Type>::toULongLong() const
{
    return this->value();
}

template <typename Type>
bool UnsignedIntegralProperty<Type>::fromULongLong(unsigned long long integral)
{
    this->setValue(static_cast<Type>(integral));
    return true;
}

template <typename Type>
std::string UnsignedIntegralProperty<Type>::matchRegex() const
{
    return "\\+?\\d+";
}

} // namespace reflectionzeug
