
#pragma once

namespace reflectionzeug
{

template <class Object>
StringProperty::StringProperty(
    Object & object,
    const std::string & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::string &))
:   ValueProperty<std::string>(object, getter_pointer, setter_pointer)
{
}
    
template <class Object>
StringProperty::StringProperty(
    Object & object, 
    std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::string &))
:   ValueProperty<std::string>(object, getter_pointer, setter_pointer)
{
}

template <class Object>
StringProperty::StringProperty(
    Object & object, 
    std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(std::string))
:   ValueProperty<std::string>(object, getter_pointer, setter_pointer)
{
}

} // namespace reflectionzeug
