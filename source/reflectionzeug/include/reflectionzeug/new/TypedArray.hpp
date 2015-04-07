
#pragma once


#include <reflectionzeug/new/TypedArray.h>


namespace reflectionzeug
{


template <typename T, size_t Size>
TypedArray<T, Size>::TypedArray(ArrayAccessor<T, Size> * accessor)
: AbstractTyped<std::array<T, Size>>(accessor)
{
}

template <typename T, size_t Size>
TypedArray<T, Size>::~TypedArray()
{
}


} // namespace reflectionzeug
