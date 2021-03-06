
#pragma once


#include <reflectionzeug/property/AccessorGetSet.h>


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
{
    m_getter = [object, getter_pointer] () -> Type
    {
        return (object->*getter_pointer)();
    };

    m_setter = [object, setter_pointer] (const Type & value)
    {
        (object->*setter_pointer)(value);
    };
}

template <typename Type>
template <class Object>
AccessorGetSet<Type>::AccessorGetSet(Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
{
    m_getter = [object, getter_pointer] () -> Type
    {
        return (object->*getter_pointer)();
    };

    m_setter = [object, setter_pointer] (const Type & value)
    {
        (object->*setter_pointer)(value);
    };
}

template <typename Type>
template <class Object>
AccessorGetSet<Type>::AccessorGetSet(Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
{
    m_getter = [object, getter_pointer] () -> Type
    {
        return (object->*getter_pointer)();
    };

    m_setter = [object, setter_pointer] (const Type & value)
    {
        (object->*setter_pointer)(value);
    };
}

template <typename Type>
AccessorGetSet<Type>::~AccessorGetSet()
{
}

template <typename Type>
AbstractAccessor * AccessorGetSet<Type>::clone() const
{
    return new AccessorGetSet<Type>(m_getter, m_setter);
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
{
    m_getter = [object, getter_pointer] () -> Type
    {
        return (object->*getter_pointer)();
    };
}

template <typename Type>
template <class Object>
AccessorGetSet<const Type>::AccessorGetSet(Object * object,
    Type (Object::*getter_pointer)() const)
{
    m_getter = [object, getter_pointer] () -> Type
    {
        return (object->*getter_pointer)();
    };
}

template <typename Type>
AccessorGetSet<const Type>::~AccessorGetSet()
{
}

template <typename Type>
AbstractAccessor * AccessorGetSet<const Type>::clone() const
{
    return new AccessorGetSet<const Type>(m_getter);
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
