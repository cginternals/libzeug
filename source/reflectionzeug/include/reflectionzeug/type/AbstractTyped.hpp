
#pragma once


#include <reflectionzeug/type/AbstractTyped.h>
#include <reflectionzeug/type/AccessorValue.h>
#include <reflectionzeug/type/AccessorGetSet.h>


namespace reflectionzeug
{


// Read/write
template <typename Type>
AbstractTyped<Type>::AbstractTyped(const std::string & name)
: AbstractProperty(name)
, m_accessor(new AccessorValue<Type>())
{
}

template <typename Type>
AbstractTyped<Type>::AbstractTyped(const std::string & name, const Type & value)
: AbstractProperty(name)
, m_accessor(new AccessorValue<Type>(value))
{
}

template <typename Type>
AbstractTyped<Type>::AbstractTyped(
    const std::string & name,
	std::function<Type ()> getter,
    std::function<void(const Type &)> setter)
: AbstractProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
AbstractTyped<Type>::AbstractTyped(
    const std::string & name,
	Object * object,
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: AbstractProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTyped<Type>::AbstractTyped(
    const std::string & name,
	Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: AbstractProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTyped<Type>::AbstractTyped(
    const std::string & name,
	Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
: AbstractProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
AbstractTyped<Type>::AbstractTyped(const std::string & name, Accessor<Type> * accessor)
: AbstractProperty(name)
, m_accessor(accessor)
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
Variant AbstractTyped<Type>::toVariant() const
{
    // By default, return variant of the exact type
    return Variant::fromValue<Type>(this->value());
}

template <typename Type>
bool AbstractTyped<Type>::fromVariant(const Variant & value)
{
    // By default, read from variant of the exact type
    if (value.hasType<Type>()) {
        setValue( value.value<Type>() );
        return true;
    }

    // Invalid value
    return false;
}

template <typename Type>
Type * AbstractTyped<Type>::ptr() const
{
    return m_accessor->ptr();
}

template <typename Type>
Type AbstractTyped<Type>::value() const
{
    return m_accessor->value();
}

template <typename Type>
void AbstractTyped<Type>::setValue(const Type & value)
{
    m_accessor->setValue(value);
    this->valueChanged(value);
    this->changed();
}


// Read-only
template <typename Type>
AbstractTyped<const Type>::AbstractTyped(const std::string & name)
: AbstractTyped<Type>(name, new AccessorValue<const Type>())
{
}

template <typename Type>
AbstractTyped<const Type>::AbstractTyped(const std::string & name, const Type & value)
: AbstractTyped<Type>(name, new AccessorValue<const Type>(value))
{
}

template <typename Type>
AbstractTyped<const Type>::AbstractTyped(
    const std::string & name,
    std::function<Type ()> getter)
: AbstractTyped<Type>(name, new AccessorGetSet<const Type>(getter))
{
}

template <typename Type>
template <class Object>
AbstractTyped<const Type>::AbstractTyped(
    const std::string & name,
    Object * object,
    const Type & (Object::*getter_pointer)() const)
: AbstractTyped<Type>(name, new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTyped<const Type>::AbstractTyped(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)() const)
: AbstractTyped<Type>(name, new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
AbstractTyped<const Type>::AbstractTyped(const std::string & name, Accessor<const Type> * accessor)
: AbstractTyped<Type>(name, accessor)
{
}

template <typename Type>
AbstractTyped<const Type>::~AbstractTyped()
{
}


} // namespace reflectionzeug
