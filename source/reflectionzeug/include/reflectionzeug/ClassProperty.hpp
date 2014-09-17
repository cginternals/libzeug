#pragma once

#include <reflectionzeug/ClassProperty.h>

#include <limits>
#include <iostream>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
ClassProperty<Type>::ClassProperty(Arguments&&... args)
:   ValueProperty<Type>(std::forward<Arguments>(args)...)
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
