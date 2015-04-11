
#pragma once


#include <reflectionzeug/new/Property.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
Property2<T>::Property2(const std::string & name, Args&&... args)
: Typed<T>::Typed(std::forward<Args>(args)...)
, AbstractProperty2(name)
{
}

template <typename T>
Property2<T>::~Property2()
{
}

template <typename T>
std::string Property2<T>::name() const
{
    return m_name;
}

template <typename T>
bool Property2<T>::setName(const std::string & name)
{
    m_name = name;
    return true;
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
