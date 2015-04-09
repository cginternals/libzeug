
#pragma once


#include <reflectionzeug/new/Property.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
Property2<T>::Property2(Args&&... args)
: Typed<T>::Typed(std::forward<Args>(args)...)
{
}

template <typename T>
Property2<T>::~Property2()
{
}


} // namespace reflectionzeug
