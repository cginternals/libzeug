
#pragma once


#include <reflectionzeug/type/Typed.h>
#include <reflectionzeug/type/AccessorValue.h>
#include <reflectionzeug/type/AccessorGetSet.h>


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
    visitor->callVisitor<Typed<T>>(this);

    // Let base classes also call the visitor, e.g., for compound types
    return TypeSelector<T>::Type::accept(visitor);
}

template <typename T>
AbstractValue * Typed<T>::createCopy() const
{
    return new Typed<T>(this->getValue());
}


} // namespace reflectionzeug
