
#pragma once


#include <reflectionzeug/new/TypedArray.h>
#include <reflectionzeug/new/AbstractVisitor.h>


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
    // Call visitor->visit(TypedArray<T, Size>)
    auto * typedVisitor = visitor->asVisitor<TypedArray<T, Size>>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }

    // Call visitor->visit(AbstractCollection)
    auto * interfaceVisitor = visitor->asVisitor<AbstractCollection>();
    if (interfaceVisitor) {
        interfaceVisitor->visit(this);
    }
}


} // namespace reflectionzeug
