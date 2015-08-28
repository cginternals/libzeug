
#pragma once


#include <reflectionzeug/property/PropertyString.h>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyString<T>::PropertyString(Args&&... args)
: AbstractTypedProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyString<T>::~PropertyString()
{
}

template <typename T>
std::string PropertyString<T>::toString() const
{
    return this->value();
}

template <typename T>
bool PropertyString<T>::fromString(const std::string & string)
{
    this->setValue(string);
    return true;
}

template <typename T>
void PropertyString<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyString<T>>(this);
    visitor->callVisitor<AbstractStringInterface>(this);
}


} // namespace reflectionzeug
