#pragma once

#include <reflectionzeug/ValueProperty.h>

#include <typeinfo>

#include <reflectionzeug/PropertyVisitor.h>
#include <reflectionzeug/StoredValue.h>
#include <reflectionzeug/AccessorValue.h>
#include <reflectionzeug/Variant.h>

namespace reflectionzeug
{

template <typename Type, typename SuperClass>
ValueProperty<Type, SuperClass>::ValueProperty(const Type & value)
:   m_value(new StoredValue<Type>(value))
{
    init();
}

template <typename Type, typename SuperClass>
ValueProperty<Type, SuperClass>::ValueProperty(
    const std::function<Type ()> & getter,
    const std::function<void(const Type &)> & setter)
:   m_value(new AccessorValue<Type>(getter, setter))
{
    init();
}

template <typename Type, typename SuperClass>
template <class Object>
ValueProperty<Type, SuperClass>::ValueProperty(
    Object * object, 
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
    init();
}
    
template <typename Type, typename SuperClass>
template <class Object>
ValueProperty<Type, SuperClass>::ValueProperty(
    Object * object, 
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
    init();
}
    
template <typename Type, typename SuperClass>
template <class Object>
ValueProperty<Type, SuperClass>::ValueProperty(
    Object * object, 
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
    init();
}
    
template <typename Type, typename SuperClass>
ValueProperty<Type, SuperClass>::~ValueProperty()
{
}

template <typename Type, typename SuperClass>
Type ValueProperty<Type, SuperClass>::value() const
{
    return m_value->get();
}

template <typename Type, typename SuperClass>
void ValueProperty<Type, SuperClass>::setValue(const Type & value)
{
    m_value->set(value);
    this->ValueProperty::valueChanged(value);
}

template <typename Type, typename SuperClass>
size_t ValueProperty<Type, SuperClass>::stype()
{
    static size_t type = typeid(Type).hash_code();
    return type;
}

template <typename Type, typename SuperClass>
size_t ValueProperty<Type, SuperClass>::type() const
{
    return stype();
}

template <typename Type, typename SuperClass>
Variant ValueProperty<Type, SuperClass>::toVariant() const
{
    return Variant::fromValue<Type>(m_value->get());
}

template <typename Type, typename SuperClass>
bool ValueProperty<Type, SuperClass>::fromVariant(const Variant & variant)
{
    if (!variant.canConvert<Type>())
        return false;

    m_value->set(variant.value<Type>());
    return true;
}

template <typename Type, typename SuperClass>
void ValueProperty<Type, SuperClass>::init()
{
    this->valueChanged.connect([this] (const Type &)
    {
        this->AbstractValueProperty::valueChanged();
    });
}

} // namespace reflectionzeug
