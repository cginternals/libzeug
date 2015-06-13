
#pragma once


#include <reflectionzeug/PropertyGroup.h>


namespace reflectionzeug
{


template <typename Type>
Property2<Type> * PropertyGroup::property(const std::string & path)
{
    // Get property by path
    AbstractProperty2 * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into requested type
    return property->as<Property2<Type>>();
}

template <typename Type>
const Property2<Type> * PropertyGroup::property(const std::string & path) const
{
    // Get property by path
    const AbstractProperty2 * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into requested type
    return property->as<Property2<Type>>();
}

template <typename Type, typename... Args>
Property2<Type> * PropertyGroup::addProperty(const std::string & name, Args&&... args)
{
    // Create new property
    auto property = new Property2<Type>(name, std::forward<Args>(args)...);
    if (this->addProperty(property))
    {
        return property;
    }

    // Error, delete property and return
    delete property;
    return nullptr;
}

template <typename Type>
Type PropertyGroup::value(const std::string & path) const
{
    // Get property by path
    const AbstractProperty2 * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into requested type
    Property2<Type> * typed = property->as<Property2<Type>>();
    if (!typed) {
        return nullptr;
    }

    // Get value
    return typed->value();
}

template <typename Type>
void PropertyGroup::setValue(const std::string & path, const Type & value)
{
    // Get property by path
    const AbstractProperty2 * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into requested type
    Property2<Type> * typed = property->as<Property2<Type>>();
    if (!typed) {
        return nullptr;
    }

    // Set value
    typed->setValue(value);
}


} // namespace reflectionzeug
