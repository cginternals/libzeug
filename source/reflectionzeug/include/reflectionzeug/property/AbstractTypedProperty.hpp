
#pragma once


#include <reflectionzeug/property/AbstractTypedProperty.h>

#include <reflectionzeug/property/AccessorGetSet.h>


namespace reflectionzeug
{


// Read/write
template <typename Type>
AbstractTypedProperty<Type>::AbstractTypedProperty(
    const std::string & name,
    std::function<Type ()> getter,
    std::function<void(const Type &)> setter)
: AbstractValueProperty(name)
, m_accessor(new AccessorGetSet<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
AbstractTypedProperty<Type>::AbstractTypedProperty(
    const std::string & name,
    Object * object,
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: AbstractValueProperty(name)
, m_accessor(new AccessorGetSet<Type>(object, getter_pointer, setter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTypedProperty<Type>::AbstractTypedProperty(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: AbstractValueProperty(name)
, m_accessor(new AccessorGetSet<Type>(object, getter_pointer, setter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTypedProperty<Type>::AbstractTypedProperty(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
: AbstractValueProperty(name)
, m_accessor(new AccessorGetSet<Type>(object, getter_pointer, setter_pointer))
{
}

template <typename Type>
AbstractTypedProperty<Type>::AbstractTypedProperty(const std::string & name, Accessor<Type> * accessor)
: AbstractValueProperty(name)
, m_accessor(accessor)
{
}

template <typename Type>
AbstractTypedProperty<Type>::~AbstractTypedProperty()
{
}

template <typename Type>
Type AbstractTypedProperty<Type>::value() const
{
    return m_accessor->value();
}

template <typename Type>
void AbstractTypedProperty<Type>::setValue(const Type & value)
{
    m_accessor->setValue(value);
    this->valueChanged(value);
    this->changed();
}

template <typename Type>
const std::type_info & AbstractTypedProperty<Type>::type() const
{
    return typeid(Type);
}

template <typename Type>
Variant AbstractTypedProperty<Type>::toVariant() const
{
    // By default, return variant of the exact type
    return Variant::fromValue<Type>(this->value());
}

template <typename Type>
bool AbstractTypedProperty<Type>::fromVariant(const Variant & value)
{
    // By default, read from variant of the exact type
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        setValue( value.value<Type>() );
        return true;
    }

    // Invalid value
    return false;
}


// Read-only
template <typename Type>
AbstractTypedProperty<const Type>::AbstractTypedProperty(
    const std::string & name,
    std::function<Type ()> getter)
: AbstractTypedProperty<Type>(name, new AccessorGetSet<const Type>(getter))
{
}

template <typename Type>
template <class Object>
AbstractTypedProperty<const Type>::AbstractTypedProperty(
    const std::string & name,
    Object * object,
    const Type & (Object::*getter_pointer)() const)
: AbstractTypedProperty<Type>(name, new AccessorGetSet<const Type>(object, getter_pointer))
{
}

template <typename Type>
template <class Object>
AbstractTypedProperty<const Type>::AbstractTypedProperty(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)() const)
: AbstractTypedProperty<Type>(name, new AccessorGetSet<const Type>(object, getter_pointer))
{
}

template <typename Type>
AbstractTypedProperty<const Type>::AbstractTypedProperty(const std::string & name, Accessor<const Type> * accessor)
: AbstractTypedProperty<Type>(name, accessor)
{
}

template <typename Type>
AbstractTypedProperty<const Type>::~AbstractTypedProperty()
{
}


} // namespace reflectionzeug
