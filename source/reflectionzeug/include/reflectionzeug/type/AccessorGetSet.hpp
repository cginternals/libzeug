
#pragma once


#include <reflectionzeug/type/AccessorGetSet.h>


namespace reflectionzeug
{


// Read/write accessor
template <typename Type>
AccessorGetSet<Type>::AccessorGetSet(std::function<Type ()> getter,
    std::function<void(const Type &)> setter)
: m_getter(getter)
, m_setter(setter)
{
}

template <typename Type>
template <class Object>
AccessorGetSet<Type>::AccessorGetSet(Object * object,
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: m_getter(std::bind(getter_pointer, object))
, m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}

template <typename Type>
template <class Object>
AccessorGetSet<Type>::AccessorGetSet(Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: m_getter(std::bind(getter_pointer, object))
, m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}

template <typename Type>
template <class Object>
AccessorGetSet<Type>::AccessorGetSet(Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
: m_getter(std::bind(getter_pointer, object))
, m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}

template <typename Type>
AccessorGetSet<Type>::~AccessorGetSet()
{
}

template <typename Type>
Type * AccessorGetSet<Type>::ptr() const
{
    return nullptr;
}

template <typename Type>
Type AccessorGetSet<Type>::value() const
{
    return m_getter();
}

template <typename Type>
void AccessorGetSet<Type>::setValue(const Type & value)
{
    m_setter(value);
}


// Read-only accessor
template <typename Type>
AccessorGetSet<const Type>::AccessorGetSet(std::function<Type ()> getter)
: m_getter(getter)
{
}

template <typename Type>
template <class Object>
AccessorGetSet<const Type>::AccessorGetSet(Object * object,
    const Type & (Object::*getter_pointer)() const)
: m_getter(std::bind(getter_pointer, object))
{
}

template <typename Type>
template <class Object>
AccessorGetSet<const Type>::AccessorGetSet(Object * object,
    Type (Object::*getter_pointer)() const)
: m_getter(std::bind(getter_pointer, object))
{
}

template <typename Type>
AccessorGetSet<const Type>::~AccessorGetSet()
{
}

template <typename Type>
Type * AccessorGetSet<const Type>::ptr() const
{
    return nullptr;
}

template <typename Type>
Type AccessorGetSet<const Type>::value() const
{
    return m_getter();
}


} // namespace reflectionzeug
