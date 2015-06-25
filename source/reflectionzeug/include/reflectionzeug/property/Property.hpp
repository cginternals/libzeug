
#pragma once


#include <reflectionzeug/property/Property.h>

#include <reflectionzeug/property/AccessorValue.h>
#include <reflectionzeug/property/AccessorGetSet.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
Property<T>::Property(Args&&... args)
: PropertyTypeSelector<T>::Type(std::forward<Args>(args)...)
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
    return PropertyTypeSelector<T>::Type::accept(visitor);
}


} // namespace reflectionzeug
