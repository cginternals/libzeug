
#pragma once


#include <reflectionzeug/type/Property.h>
#include <reflectionzeug/type/AccessorValue.h>
#include <reflectionzeug/type/AccessorGetSet.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
Property<T>::Property(Args&&... args)
: TypeSelector<T>::Type(std::forward<Args>(args)...)
{
}

template <typename T>
Property<T>::~Property()
{
}

template <typename T>
void Property<T>::accept(AbstractVisitor * visitor)
{
    // Call visitor->visit(Property<T>)
    visitor->callVisitor<Property<T>>(this);

    // Let base classes also call the visitor, e.g., for compound types
    return TypeSelector<T>::Type::accept(visitor);
}


} // namespace reflectionzeug
