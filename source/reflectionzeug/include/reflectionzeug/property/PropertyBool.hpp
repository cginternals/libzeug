
#pragma once


#include <reflectionzeug/property/PropertyBool.h>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyBool<T>::PropertyBool(Args&&... args)
: AbstractTypedProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyBool<T>::~PropertyBool()
{
}

template <typename T>
void PropertyBool<T>::toggleValue()
{
    this->setValue(!this->value());
}

template <typename T>
bool PropertyBool<T>::toBool() const
{
    return this->value();
}

template <typename T>
bool PropertyBool<T>::fromBool(bool value)
{
    this->setValue(value);
    return true;
}

template <typename T>
std::string PropertyBool<T>::toString() const
{
    return this->value() ? "true" : "false"; 
}

template <typename T>
bool PropertyBool<T>::fromString(const std::string & string)
{
    if (!stringzeug::matchesRegex(string, "(true|false)"))
        return false;

    this->setValue(string == "true");
    return true;
}

template <typename T>
void PropertyBool<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyBool>(this);
    visitor->callVisitor<AbstractBooleanInterface>(this);
}


} // namespace reflectionzeug
