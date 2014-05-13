
#pragma once

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
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);
    
    if (typedVisitor == nullptr)
        return UnsignedIntegralPropertyInterface::accept(visitor);
    
    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

template <typename Type>
unsigned long long UnsignedIntegralProperty<Type>::uLongLongMinimum()
{
    return this->minimum();
}

template <typename Type>
bool UnsignedIntegralProperty<Type>::hasMinimum() const
{
    return NumberProperty<Type>::hasMinimum();
}

template <typename Type>
unsigned long long UnsignedIntegralProperty<Type>::uLongLongMaximum()
{
    return this->maximum();
}

template <typename Type>
bool UnsignedIntegralProperty<Type>::hasMaximum() const
{
    return NumberProperty<Type>::hasMaximum();
}

template <typename Type>
bool UnsignedIntegralProperty<Type>::hasRange() const
{
    return NumberProperty<Type>::hasRange();
}

template <typename Type>
unsigned long long UnsignedIntegralProperty<Type>::uLongLongStep()
{
    return this->step();
}

template <typename Type>
bool UnsignedIntegralProperty<Type>::hasStep() const
{
    return NumberProperty<Type>::hasStep();
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
