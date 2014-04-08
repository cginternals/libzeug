
#pragma once

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
SignedIntegralProperty<Type>::SignedIntegralProperty(Arguments&&... args)
:   NumberProperty<Type>(std::forward<Arguments>(args)...)
{
}

template <typename Type>
void SignedIntegralProperty<Type>::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);
    
    if (typedVisitor == nullptr)
    {
        SignedIntegralPropertyInterface::accept(visitor, warn);
        return;
    }
    
    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

template <typename Type>
long long SignedIntegralProperty<Type>::uLongLongMinimum()
{
    return this->minimum();
}

template <typename Type>
bool SignedIntegralProperty<Type>::hasMinimum() const
{
    return NumberProperty<Type>::hasMinimum();
}

template <typename Type>
long long SignedIntegralProperty<Type>::uLongLongMaximum()
{
    return this->maximum();
}

template <typename Type>
bool SignedIntegralProperty<Type>::hasMaximum() const
{
    return NumberProperty<Type>::hasMaximum();
}

template <typename Type>
bool SignedIntegralProperty<Type>::hasRange() const
{
    return NumberProperty<Type>::hasRange();
}

template <typename Type>
long long SignedIntegralProperty<Type>::uLongLongStep()
{
    return this->step();
}

template <typename Type>
bool SignedIntegralProperty<Type>::hasStep() const
{
    return NumberProperty<Type>::hasStep();
}

template <typename Type>
long long SignedIntegralProperty<Type>::toULongLong() const
{
    return this->value();
}

template <typename Type>
bool SignedIntegralProperty<Type>::fromULongLong(long long integral)
{
    this->setValue(static_cast<Type>(integral));
}

template <typename Type>
std::string SignedIntegralProperty<Type>::matchRegex()
{
    return "(-|\\+)?\\d+";
}

} // namespace reflectionzeug
