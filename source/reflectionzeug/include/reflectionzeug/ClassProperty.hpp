
#pragma once

#include <limits>
#include <iostream>

namespace reflectionzeug
{

template <typename Type>
ClassProperty<Type>::ClassProperty(const Type & value)
:   ValueProperty<Type>(value)
{
}

template <typename Type>
ClassProperty<Type>::ClassProperty( 
    const std::function<Type ()> & getter,
    const std::function<void(const Type &)> & setter)
:   ValueProperty<Type>(getter, setter)
{
}

template <typename Type>
template <class Object>
ClassProperty<Type>::ClassProperty(
    Object & object, 
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValueProperty<Type>(object, getter_pointer, setter_pointer)
{
}

template <typename Type>
template <class Object>
ClassProperty<Type>::ClassProperty(
    Object & object, 
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValueProperty<Type>(object, getter_pointer, setter_pointer)
{
}

template <typename Type>
template <class Object>
ClassProperty<Type>::ClassProperty(
    Object & object, 
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   ValueProperty<Type>(object, getter_pointer, setter_pointer)
{
}

template <typename Type>
ClassProperty<Type>::~ClassProperty()
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
