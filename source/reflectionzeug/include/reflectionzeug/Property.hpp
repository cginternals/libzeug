
#pragma once


#include <reflectionzeug/Property.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
Property<T>::Property(const std::string & name, Args&&... args)
: NamedTyped<T>::NamedTyped(name, std::forward<Args>(args)...)
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

    // Let base classes call the visitor
    return Typed<T>::accept(visitor);
}


} // namespace reflectionzeug
