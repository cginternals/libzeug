
#pragma once


#include <iostream>

#include <reflectionzeug/type/PropertyClass.h>
#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyClass<T>::PropertyClass(Args&&... args)
: AbstractPropertyValue<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyClass<T>::~PropertyClass()
{
}

template <typename T>
void PropertyClass<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyClass<T>>(this);
}


} // namespace reflectionzeug
