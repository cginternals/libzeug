
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>
#include <reflectionzeug/new/AccessorValue.h>
#include <reflectionzeug/new/AccessorGetSet.h>


namespace reflectionzeug
{


// Read/write
template <typename Type>
AbstractTyped<Type>::AbstractTyped()
: m_accessor(new AccessorValue<Type>())
{
}

template <typename Type>
AbstractTyped<Type>::AbstractTyped(const Type & value)
: m_accessor(new AccessorValue<Type>(value))
{
}

template <typename Type>
AbstractTyped<Type>::AbstractTyped(
	std::function<Type ()> getter,
    std::function<void(const Type &)> setter)
: m_accessor(new AccessorGetSet<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
AbstractTyped<Type>::AbstractTyped(
	Object * object,
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: m_accessor(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTyped<Type>::AbstractTyped(
	Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: m_accessor(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTyped<Type>::AbstractTyped(
	Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
: m_accessor(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
AbstractTyped<Type>::AbstractTyped(Accessor<Type> * accessor)
: m_accessor(accessor)
{
}

template <typename Type>
AbstractTyped<Type>::~AbstractTyped()
{
}

template <typename Type>
const std::type_info & AbstractTyped<Type>::type() const
{
    return typeid(Type);
}

template <typename Type>
Type AbstractTyped<Type>::getValue() const
{
    return m_accessor->getValue();
}

template <typename Type>
void AbstractTyped<Type>::setValue(const Type & value)
{
    m_accessor->setValue(value);
    this->valueChanged();
}


// Read-only
template <typename Type>
AbstractTyped<const Type>::AbstractTyped()
: AbstractTyped<Type>(new AccessorValue<const Type>())
{
}

template <typename Type>
AbstractTyped<const Type>::AbstractTyped(const Type & value)
: AbstractTyped<Type>(new AccessorValue<const Type>(value))
{
}

template <typename Type>
AbstractTyped<const Type>::AbstractTyped(
    std::function<Type ()> getter)
: AbstractTyped<Type>(new AccessorGetSet<const Type>(getter))
{
}

template <typename Type>
template <class Object>
AbstractTyped<const Type>::AbstractTyped(
    Object * object,
    const Type & (Object::*getter_pointer)() const)
: AbstractTyped<Type>(new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTyped<const Type>::AbstractTyped(
    Object * object,
    Type (Object::*getter_pointer)() const)
: AbstractTyped<Type>(new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
AbstractTyped<const Type>::AbstractTyped(Accessor<const Type> * accessor)
: AbstractTyped<Type>(accessor)
{
}

template <typename Type>
AbstractTyped<const Type>::~AbstractTyped()
{
}


} // namespace reflectionzeug