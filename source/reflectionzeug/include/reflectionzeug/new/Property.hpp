
#pragma once


#include <reflectionzeug/new/Property.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
Property2<T>::Property2(Args&&... args)
: Typed<T>::Typed(std::forward<Args>(args)...)
{
}

template <typename T>
Property2<T>::~Property2()
{
}

template <typename T>
void Property2<T>::accept(AbstractVisitor * visitor)
{
    // Call visitor->visit(Property<T>)
    visitor->callVisitor<Property2<T>>(this);

    // Let base classes call the visitor
    return Typed<T>::accept(visitor);
}


} // namespace reflectionzeug
