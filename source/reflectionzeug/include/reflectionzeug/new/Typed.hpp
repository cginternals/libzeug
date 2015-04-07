
#pragma once


#include <reflectionzeug/new/Typed.h>
#include <reflectionzeug/new/AccessorValue.h>
#include <reflectionzeug/new/AccessorGetSet.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
Typed<T>::Typed(Args&&... args)
: TypeSelector<T>::Type(std::forward<Args>(args)...)
{
}

template <typename T>
Typed<T>::~Typed()
{
}


} // namespace reflectionzeug
