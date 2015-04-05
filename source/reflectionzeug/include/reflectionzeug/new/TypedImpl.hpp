
#pragma once


#include <reflectionzeug/new/TypedImpl.h>


namespace reflectionzeug
{


template <typename T>
TypedImpl<T>::TypedImpl(Accessor<T> * accessor)
: TypeSelector<T>::Type(accessor)
{
}

template <typename T>
TypedImpl<T>::~TypedImpl()
{
}


} // namespace reflectionzeug
