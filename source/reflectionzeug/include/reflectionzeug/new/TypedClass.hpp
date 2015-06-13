
#pragma once


#include <iostream>
#include <reflectionzeug/new/TypedClass.h>
#include <reflectionzeug/new/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
TypedClass<T>::TypedClass(Args&&... args)
: AbstractTyped<T>(std::forward<Args>(args)...)
{
}

template <typename T>
TypedClass<T>::~TypedClass()
{
}

template <typename T>
void TypedClass<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedClass<T>>(this);
}


} // namespace reflectionzeug
