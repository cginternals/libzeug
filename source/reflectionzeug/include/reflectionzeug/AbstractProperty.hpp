#pragma once

#include <reflectionzeug/AbstractProperty.h>

namespace reflectionzeug
{

template <typename T>
T AbstractProperty::option(const std::string & key, const T & defaultValue) const
{
    return hasOption(key) ? option(key).value<T>(defaultValue) : defaultValue;
}

template <typename T>
void AbstractProperty::setOption(const std::string & key, const T & value)
{
    setOption(key, Variant::fromValue<T>(value));
}

template <class Property>
Property * AbstractProperty::as()
{
    Property * property = dynamic_cast<Property *>(this);
    assert(property);
    return property;
}

template <class Property>
const Property * AbstractProperty::as() const
{
    const Property * property = dynamic_cast<const Property *>(this);
    assert(property);
    return property;
}

} // namespace reflectionzeug
