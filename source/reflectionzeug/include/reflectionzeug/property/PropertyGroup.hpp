
#pragma once


#include <reflectionzeug/property/PropertyGroup.h>
#include <reflectionzeug/property/Property.h>


namespace reflectionzeug
{


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
Property<Type> * PropertyGroup::property(const std::string & name)
{
    // Get property by path
    Property<Type> * property = this->property(name)->as<Property<Type>>();
    if (!property) {
        return nullptr;
    }

    return property;
}

template <typename Type>
const Property<Type> * PropertyGroup::property(const std::string & name) const
{
    // Get property by path
    const Property<Type> * property = this->property(name)->as<Property<Type>>();
    if (!property) {
        return nullptr;
    }

    return property;
}

template <typename Type>
Type PropertyGroup::value(const std::string & path) const
{
    // Get property by path
    const AbstractProperty * property = this->property(path);
    if (!property) {
        return Type();
    }

    // Convert into requested type
    const Property<Type> * typed = property->as<const Property<Type>>();
    if (!typed) {
        return Type();
    }

    // Get value
    return typed->value();
}

template <typename Type>
void PropertyGroup::setValue(const std::string & path, const Type & value)
{
    // Get property by path
    AbstractProperty * property = this->property(path);
    if (!property) {
        return;
    }

    // Convert into requested type
    Property<Type> * typed = property->as<Property<Type>>();
    if (!typed) {
        return;
    }

    // Set value
    typed->setValue(value);
}


} // namespace reflectionzeug
