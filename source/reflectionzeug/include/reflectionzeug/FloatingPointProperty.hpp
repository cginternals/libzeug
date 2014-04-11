
#pragma once

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
FloatingPointProperty<Type>::FloatingPointProperty(Arguments&&... args)
:   NumberProperty<Type>(std::forward<Arguments>(args)...)
,   m_precision(0)
{
}

template <typename Type>
void FloatingPointProperty<Type>::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);
    
    if (typedVisitor == nullptr)
    {
        FloatingPointPropertyInterface::accept(visitor, warn);
        return;
    }
    
    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

template <typename Type>
double FloatingPointProperty<Type>::doubleMinimum() const
{
    return this->minimum();
}

template <typename Type>
bool FloatingPointProperty<Type>::hasMinimum() const
{
    return NumberProperty<Type>::hasMinimum();
}

template <typename Type>
double FloatingPointProperty<Type>::doubleMaximum() const
{
    return this->maximum();
}

template <typename Type>
bool FloatingPointProperty<Type>::hasMaximum() const
{
    return NumberProperty<Type>::hasMaximum();
}

template <typename Type>
bool FloatingPointProperty<Type>::hasRange() const
{
    return NumberProperty<Type>::hasRange();
}

template <typename Type>
double FloatingPointProperty<Type>::doubleStep() const
{
    return this->step();
}

template <typename Type>
bool FloatingPointProperty<Type>::hasStep() const
{
    return NumberProperty<Type>::hasStep();
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
std::string FloatingPointProperty<Type>::matchRegex()
{
    return "(-|\\+)?\\d+\\.?\\d*";
}

template <typename Type>
unsigned int FloatingPointProperty<Type>::precision() const
{
    return m_precision;
}

template <typename Type>
void FloatingPointProperty<Type>::setPrecision(unsigned int precision)
{
    m_precision = precision;
}

template <typename Type>
bool FloatingPointProperty<Type>::hasPrecision() const
{
    return m_precision != 0;
}

} // namespace reflectionzeug
