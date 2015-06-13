
#pragma once


#include <reflectionzeug/TypedArray.h>
#include <reflectionzeug/AbstractVisitor.h>


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

template <typename T, size_t Size>
void TypedArray<T, Size>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedArray<T, Size>>(this);
    visitor->callVisitor<AbstractCollection>(this);
}


} // namespace reflectionzeug
