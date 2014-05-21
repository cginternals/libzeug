
#pragma once

#include <reflectionzeug/Property.h>


namespace reflectionzeug
{

template <typename Type>
Property<Type> * PropertyGroup::addProperty(const std::string & name, const Type & value)
{
    auto property = new Property<Type>(name, value);

    if (this->addProperty(property))
        return property;

    delete property;
    return nullptr;
}

template <typename Type, typename... Args>
Property<Type> * PropertyGroup::addProperty(const std::string & name, Args&&... args)
{
    auto property = new Property<Type>(name, std::forward<Args>(args)...);

    if (this->addProperty(property))
        return property;

    delete property;
    return nullptr;
}

template <typename Type>
Property<Type> * PropertyGroup::property(const std::string & name)
{
    return this->property(name)->as<Property<Type>>();
}
    
template <typename Type>
const Property<Type> * PropertyGroup::property(const std::string & name) const
{
    return this->property(name)->as<Property<Type>>();
}

template <typename Type>
Type PropertyGroup::value(const std::string & name) const
{
    return this->property(name)->as<Property<Type>>()->value();
}

template <typename Type>
void PropertyGroup::setValue(const std::string & name, const Type & value)
{
    this->property(name)->as<Property<Type>>()->setValue(value);
}

} // namespace reflectionzeug
