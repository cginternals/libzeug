
#pragma once


#include <reflectionzeug/new/AccessorGetSet.h>


namespace reflectionzeug
{


// Read/write accessor
template <typename T>
AccessorGetSet<T>::AccessorGetSet(std::function<T ()> getter,
    std::function<void(const T &)> setter)
: m_getter(getter)
, m_setter(setter)
{
}

template <typename T>
template <class Object>
AccessorGetSet<T>::AccessorGetSet(Object * object,
    const T & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const T &))
: m_getter(std::bind(getter_pointer, object))
, m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}

template <typename T>
template <class Object>
AccessorGetSet<T>::AccessorGetSet(Object * object,
    T (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const T &))
: m_getter(std::bind(getter_pointer, object))
, m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}

template <typename T>
template <class Object>
AccessorGetSet<T>::AccessorGetSet(Object * object,
    T (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(T))
: m_getter(std::bind(getter_pointer, object))
, m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}

template <typename T>
AccessorGetSet<T>::~AccessorGetSet()
{
}

template <typename T>
T AccessorGetSet<T>::get() const
{
    return m_getter();
}

template <typename T>
void AccessorGetSet<T>::set(const T & value)
{
    m_setter(value);
}


// Read-only accessor
template <typename T>
AccessorGetSet<const T>::AccessorGetSet(std::function<T ()> getter)
: m_getter(getter)
{
}

template <typename T>
template <class Object>
AccessorGetSet<const T>::AccessorGetSet(Object * object,
    const T & (Object::*getter_pointer)() const)
: m_getter(std::bind(getter_pointer, object))
{
}

template <typename T>
template <class Object>
AccessorGetSet<const T>::AccessorGetSet(Object * object,
    T (Object::*getter_pointer)() const)
: m_getter(std::bind(getter_pointer, object))
{
}

template <typename T>
AccessorGetSet<const T>::~AccessorGetSet()
{
}

template <typename T>
T AccessorGetSet<const T>::get() const
{
    return m_getter();
}


} // namespace reflectionzeug
