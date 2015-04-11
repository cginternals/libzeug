
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

template <typename T>
void Typed<T>::accept(AbstractVisitor * visitor)
{
    // Call visitor->visit(Typed<T>)
    auto * typedVisitor = visitor->asVisitor<Typed<T>>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }

    // Let base classes also call the visitor, e.g., for compound types
    return TypeSelector<T>::Type::accept(visitor);
}


} // namespace reflectionzeug
