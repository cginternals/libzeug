
#pragma once

namespace reflectionzeug
{

template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object
,   const std::string & (Object::*getter_pointer)() const
,   void (Object::*setter_pointer)(const std::string &))
:   ValuePropertyInterface(name)
,   ValueProperty<std::string>(name, object, getter_pointer, setter_pointer)
{
}
    
template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object, std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::string &))
:   ValuePropertyInterface(name)
,   ValueProperty<std::string>(name, object, getter_pointer, setter_pointer)
{
}

template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object, std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(std::string))
:   ValuePropertyInterface(name)
,   ValueProperty<std::string>(name, object, getter_pointer, setter_pointer)
{
}

} // namespace reflectionzeug
