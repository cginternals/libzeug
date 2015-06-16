
#pragma once


#include <reflectionzeug/property/PropertyArray.h>
#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T, size_t Size>
template <typename... Args>
PropertyArray<T, Size>::PropertyArray(Args&&... args)
: AbstractArrayProperty<T, Size>(std::forward<Args>(args)...)
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
