
#pragma once


#include <reflectionzeug/property/PropertyGroup.h>


namespace reflectionzeug
{


template <typename Type>
Property<Type> * PropertyGroup::property(const std::string & path)
{
    // Get property by path
    AbstractProperty * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into requested type
    return property->as<Property<Type>>();
}

template <typename Type>
const Property<Type> * PropertyGroup::property(const std::string & path) const
{
    // Get property by path
    const AbstractProperty * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into requested type
    return property->as<Property<Type>>();
}

template <typename Type, typename... Args>
Property<Type> * PropertyGroup::addProperty(const std::string & name, Args&&... args)
{
    // Create new property
    auto property = new Property<Type>(name, std::forward<Args>(args)...);
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
    const AbstractProperty * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into requested type
    Property<Type> * typed = property->as<Property<Type>>();
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
    const AbstractProperty * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into requested type
    Property<Type> * typed = property->as<Property<Type>>();
    if (!typed) {
        return nullptr;
    }

    // Set value
    typed->setValue(value);
}


} // namespace reflectionzeug
