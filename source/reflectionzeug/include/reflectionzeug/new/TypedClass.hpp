
#pragma once


#include <iostream>
#include <reflectionzeug/new/TypedClass.h>


namespace reflectionzeug
{


template <typename T, typename Accessor>
TypedClass<T, Accessor>::TypedClass(const Accessor & accessor)
: TypedBase<T, Accessor>(accessor)
{
}

template <typename T, typename Accessor>
TypedClass<T, Accessor>::~TypedClass()
{
}

template <typename T, typename Accessor>
std::string TypedClass<T, Accessor>::toString() const
{
    return this->get().toString();
}

template <typename T, typename Accessor>
bool TypedClass<T, Accessor>::fromString(const std::string & string)
{
    bool ok;
    T value = T::fromString(string, &ok);

    if (!ok) {
        std::cout << "Could not read from string." << std::endl;
        return false;
    }

    this->set(value);
    return true;
}


} // namespace reflectionzeug
