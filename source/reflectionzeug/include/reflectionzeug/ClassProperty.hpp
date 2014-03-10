
#pragma once

#include <limits>
#include <iostream>

namespace reflectionzeug
{

template <typename Type>
ClassProperty<Type>::ClassProperty(const std::string & name, const Type & value)
:   ValuePropertyInterface(name)
,   ValueProperty<Type>(name, value)
{
}

template <typename Type>
ClassProperty<Type>::ClassProperty(const std::string & name, 
    const std::function<Type ()> & getter,
    const std::function<void(const Type &)> & setter)
:   ValuePropertyInterface(name)
,   ValueProperty<Type>(name, getter, setter)
{
}

template <typename Type>
template <class Object>
ClassProperty<Type>::ClassProperty(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValuePropertyInterface(name)
,   ValueProperty<Type>(name, object, getter_pointer, setter_pointer)
{
}

template <typename Type>
template <class Object>
ClassProperty<Type>::ClassProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValuePropertyInterface(name)
,   ValueProperty<Type>(name, object, getter_pointer, setter_pointer)
{
}

template <typename Type>
template <class Object>
ClassProperty<Type>::ClassProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   ValuePropertyInterface(name)
,   ValueProperty<Type>(name, object, getter_pointer, setter_pointer)
{
}

template <typename Type>
std::string ClassProperty<Type>::toString() const
{
    return this->value().toString();
}

template <typename Type>
bool ClassProperty<Type>::fromString(const std::string & string)
{
    bool ok;
    Type value = Type::fromString(string, &ok);

    if (!ok)
    {
        std::cout << "Could not read from string." << std::endl;
        return false;
    }

    this->setValue(value);
    return true;
}

} // namespace reflectionzeug
