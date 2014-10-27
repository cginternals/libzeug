#pragma once

#include <reflectionzeug/ValueProperty.h>

#include <typeinfo>

#include <reflectionzeug/AccessorValue.h>
#include <reflectionzeug/StoredValue.h>
#include <reflectionzeug/Variant.h>

namespace reflectionzeug
{

template <typename Type>
ValueProperty<Type>::ValueProperty(const Type & value)
:   m_value(new StoredValue<Type>(value))
{
    init();
}

template <typename Type>
ValueProperty<Type>::ValueProperty(
    const std::function<Type ()> & getter,
    const std::function<void(const Type &)> & setter)
:   m_value(new AccessorValue<Type>(getter, setter))
{
    init();
}

template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(
    Object * object, 
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
    init();
}
    
template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(
    Object * object, 
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
    init();
}
    
template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(
    Object * object, 
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
    init();
}
    
template <typename Type>
ValueProperty<Type>::~ValueProperty()
{
}

template <typename Type>
Type ValueProperty<Type>::value() const
{
    return m_value->get();
}

template <typename Type>
void ValueProperty<Type>::setValue(const Type & value)
{
    m_value->set(value);
    this->ValueProperty::valueChanged(value);
}

template <typename Type>
size_t ValueProperty<Type>::stype()
{
    static size_t type = typeid(Type).hash_code();
    return type;
}

template <typename Type>
size_t ValueProperty<Type>::type() const
{
    return stype();
}

template <typename Type>
Variant ValueProperty<Type>::toVariant() const
{
    return Variant::fromValue<Type>(m_value->get());
}

template <typename Type>
bool ValueProperty<Type>::fromVariant(const Variant & variant)
{
    if (!variant.canConvert<Type>())
        return false;

    m_value->set(variant.value<Type>());
    return true;
}

template <typename Type>
void ValueProperty<Type>::init()
{
    ValueProperty<Type>::valueChanged.connect([this] (const Type &)
    {
        this->AbstractValueProperty::valueChanged();
    });
}

} // namespace reflectionzeug
