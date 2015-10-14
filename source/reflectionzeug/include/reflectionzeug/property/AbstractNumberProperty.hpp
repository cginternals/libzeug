
#pragma once


#include <reflectionzeug/property/AbstractNumberProperty.h>

#include <limits>
#include <sstream>

#include <stringzeug/conversion.h>
#include <stringzeug/regex.h>


namespace reflectionzeug
{


template <typename Type>
template <typename... Args>
AbstractNumberProperty<Type>::AbstractNumberProperty(Args&&... args)
: AbstractTypedProperty<Type>(std::forward<Args>(args)...)
{
    this->setOptions({
        { "minimum", Variant(std::numeric_limits<Type>::lowest()) },
        { "maximum", Variant(std::numeric_limits<Type>::max()) }
    });
}

template <typename Type>
AbstractNumberProperty<Type>::~AbstractNumberProperty()
{
}

template <typename Type>
std::string AbstractNumberProperty<Type>::toString() const
{
    // Convert number to string
    return stringzeug::toString(this->value());
}

template <typename Type>
bool AbstractNumberProperty<Type>::fromString(const std::string & string)
{
    // Check if string conforms to the specified format
    if (!stringzeug::matchesRegex(string, matchRegex()))
        return false;

    // Convert string to number
    this->setValue(stringzeug::fromString<Type>(string));
    return true;
}


} // namespace reflectionzeug
