
#pragma once


#include <reflectionzeug/property/AbstractValueProperty.h>
#include <reflectionzeug/property/AccessorValue.h>
#include <reflectionzeug/property/AccessorGetSet.h>


namespace reflectionzeug
{


// Read/write
template <typename Type>
AbstractValueProperty<Type>::AbstractValueProperty(const std::string & name)
: AbstractProperty(name)
, m_accessor(new AccessorValue<Type>())
{
}

template <typename Type>
AbstractValueProperty<Type>::AbstractValueProperty(const std::string & name, const Type & value)
: AbstractProperty(name)
, m_accessor(new AccessorValue<Type>(value))
{
}

template <typename Type>
AbstractValueProperty<Type>::AbstractValueProperty(
    const std::string & name,
	std::function<Type ()> getter,
    std::function<void(const Type &)> setter)
: AbstractProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
AbstractValueProperty<Type>::AbstractValueProperty(
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
AbstractValueProperty<Type>::AbstractValueProperty(
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
AbstractValueProperty<Type>::AbstractValueProperty(
    const std::string & name,
	Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
: AbstractProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
AbstractValueProperty<Type>::AbstractValueProperty(const std::string & name, Accessor<Type> * accessor)
: AbstractProperty(name)
, m_accessor(accessor)
{
}

template <typename Type>
AbstractValueProperty<Type>::~AbstractValueProperty()
{
}

template <typename Type>
const std::type_info & AbstractValueProperty<Type>::type() const
{
    return typeid(Type);
}

template <typename Type>
Variant AbstractValueProperty<Type>::toVariant() const
{
    // By default, return variant of the exact type
    return Variant::fromValue<Type>(this->value());
}

template <typename Type>
bool AbstractValueProperty<Type>::fromVariant(const Variant & value)
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
Type * AbstractValueProperty<Type>::ptr() const
{
    return m_accessor->ptr();
}

template <typename Type>
Type AbstractValueProperty<Type>::value() const
{
    return m_accessor->value();
}

template <typename Type>
void AbstractValueProperty<Type>::setValue(const Type & value)
{
    m_accessor->setValue(value);
    this->valueChanged(value);
    this->changed();
}


// Read-only
template <typename Type>
AbstractValueProperty<const Type>::AbstractValueProperty(const std::string & name)
: AbstractValueProperty<Type>(name, new AccessorValue<const Type>())
{
}

template <typename Type>
AbstractValueProperty<const Type>::AbstractValueProperty(const std::string & name, const Type & value)
: AbstractValueProperty<Type>(name, new AccessorValue<const Type>(value))
{
}

template <typename Type>
AbstractValueProperty<const Type>::AbstractValueProperty(
    const std::string & name,
    std::function<Type ()> getter)
: AbstractValueProperty<Type>(name, new AccessorGetSet<const Type>(getter))
{
}

template <typename Type>
template <class Object>
AbstractValueProperty<const Type>::AbstractValueProperty(
    const std::string & name,
    Object * object,
    const Type & (Object::*getter_pointer)() const)
: AbstractValueProperty<Type>(name, new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractValueProperty<const Type>::AbstractValueProperty(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)() const)
: AbstractValueProperty<Type>(name, new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
AbstractValueProperty<const Type>::AbstractValueProperty(const std::string & name, Accessor<const Type> * accessor)
: AbstractValueProperty<Type>(name, accessor)
{
}

template <typename Type>
AbstractValueProperty<const Type>::~AbstractValueProperty()
{
}


} // namespace reflectionzeug
