#pragma once

#include <reflectionzeug/FloatingPointProperty.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
FloatingPointProperty<Type>::FloatingPointProperty(Arguments&&... args)
:   NumberProperty<Type>(std::forward<Arguments>(args)...)
{
}

template <typename Type>
FloatingPointProperty<Type>::~FloatingPointProperty()
{
}

template <typename Type>
void FloatingPointProperty<Type>::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<Property<Type>>();
    
    if (typedVisitor == nullptr)
        return FloatingPointPropertyInterface::accept(visitor);
    
    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

template <typename Type>
double FloatingPointProperty<Type>::toDouble() const
{
    return this->value();
}

template <typename Type>
bool FloatingPointProperty<Type>::fromDouble(double integral)
{
    this->setValue(static_cast<Type>(integral));
    return true;
}

template <typename Type>
std::string FloatingPointProperty<Type>::matchRegex() const
{
    return "(-|\\+)?\\d+\\.?\\d*";
}

} // namespace reflectionzeug
