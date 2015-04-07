
#pragma once


#include <reflectionzeug/new/TypedArray.h>


namespace reflectionzeug
{


template <typename T, size_t Size>
template <typename... Args>
TypedArray<T, Size>::TypedArray(Args&&... args)
: AbstractTypedArray<T, Size>(std::forward<Args>(args)...)
{
}

template <typename T, size_t Size>
TypedArray<T, Size>::~TypedArray()
{
}


} // namespace reflectionzeug
