
#pragma once


#include <reflectionzeug/type/AbstractPropertyValue.h>
#include <reflectionzeug/type/AccessorValue.h>
#include <reflectionzeug/type/AccessorGetSet.h>


namespace reflectionzeug
{


// Read/write
template <typename Type>
AbstractPropertyValue<Type>::AbstractPropertyValue(const std::string & name)
: AbstractProperty(name)
, m_accessor(new AccessorValue<Type>())
{
}

template <typename Type>
AbstractPropertyValue<Type>::AbstractPropertyValue(const std::string & name, const Type & value)
: AbstractProperty(name)
, m_accessor(new AccessorValue<Type>(value))
{
}

template <typename Type>
AbstractPropertyValue<Type>::AbstractPropertyValue(
    const std::string & name,
	std::function<Type ()> getter,
    std::function<void(const Type &)> setter)
: AbstractProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
AbstractPropertyValue<Type>::AbstractPropertyValue(
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
AbstractPropertyValue<Type>::AbstractPropertyValue(
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
AbstractPropertyValue<Type>::AbstractPropertyValue(
    const std::string & name,
	Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
: AbstractProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
AbstractPropertyValue<Type>::AbstractPropertyValue(const std::string & name, Accessor<Type> * accessor)
: AbstractProperty(name)
, m_accessor(accessor)
{
}

template <typename Type>
AbstractPropertyValue<Type>::~AbstractPropertyValue()
{
}

template <typename Type>
const std::type_info & AbstractPropertyValue<Type>::type() const
{
    return typeid(Type);
}

template <typename Type>
Variant AbstractPropertyValue<Type>::toVariant() const
{
    // By default, return variant of the exact type
    return Variant::fromValue<Type>(this->value());
}

template <typename Type>
bool AbstractPropertyValue<Type>::fromVariant(const Variant & value)
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
Type * AbstractPropertyValue<Type>::ptr() const
{
    return m_accessor->ptr();
}

template <typename Type>
Type AbstractPropertyValue<Type>::value() const
{
    return m_accessor->value();
}

template <typename Type>
void AbstractPropertyValue<Type>::setValue(const Type & value)
{
    m_accessor->setValue(value);
    this->valueChanged(value);
    this->changed();
}


// Read-only
template <typename Type>
AbstractPropertyValue<const Type>::AbstractPropertyValue(const std::string & name)
: AbstractPropertyValue<Type>(name, new AccessorValue<const Type>())
{
}

template <typename Type>
AbstractPropertyValue<const Type>::AbstractPropertyValue(const std::string & name, const Type & value)
: AbstractPropertyValue<Type>(name, new AccessorValue<const Type>(value))
{
}

template <typename Type>
AbstractPropertyValue<const Type>::AbstractPropertyValue(
    const std::string & name,
    std::function<Type ()> getter)
: AbstractPropertyValue<Type>(name, new AccessorGetSet<const Type>(getter))
{
}

template <typename Type>
template <class Object>
AbstractPropertyValue<const Type>::AbstractPropertyValue(
    const std::string & name,
    Object * object,
    const Type & (Object::*getter_pointer)() const)
: AbstractPropertyValue<Type>(name, new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractPropertyValue<const Type>::AbstractPropertyValue(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)() const)
: AbstractPropertyValue<Type>(name, new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
AbstractPropertyValue<const Type>::AbstractPropertyValue(const std::string & name, Accessor<const Type> * accessor)
: AbstractPropertyValue<Type>(name, accessor)
{
}

template <typename Type>
AbstractPropertyValue<const Type>::~AbstractPropertyValue()
{
}


} // namespace reflectionzeug
