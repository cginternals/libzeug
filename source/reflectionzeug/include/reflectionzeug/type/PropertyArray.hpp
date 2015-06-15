
#pragma once


#include <reflectionzeug/type/PropertyArray.h>
#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T, size_t Size>
template <typename... Args>
PropertyArray<T, Size>::PropertyArray(Args&&... args)
: AbstractPropertyArray<T, Size>(std::forward<Args>(args)...)
{
}

template <typename T, size_t Size>
PropertyArray<T, Size>::~PropertyArray()
{
}

template <typename T, size_t Size>
void PropertyArray<T, Size>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyArray<T, Size>>(this);
    visitor->callVisitor<AbstractCollection>(this);
}


} // namespace reflectionzeug
