#pragma once

#include <reflectionzeug/ValueProperty.h>

#include <typeinfo>

#include <reflectionzeug/PropertyVisitor.h>
#include <reflectionzeug/Variant.h>

namespace reflectionzeug
{

template <typename Type, typename SuperClass>
ValueProperty<Type, SuperClass>::ValueProperty()
{
    this->valueChanged.connect([this] (const Type &)
    {
        this->AbstractValueProperty::valueChanged();
    });
}

template <typename Type, typename SuperClass>
ValueProperty<Type, SuperClass>::~ValueProperty() = default;

template <typename Type, typename SuperClass>
Type ValueProperty<Type, SuperClass>::value() const
{
    return m_getter();
}

template <typename Type, typename SuperClass>
void ValueProperty<Type, SuperClass>::setValue(const Type & value)
{
    m_setter(value);
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
    return Variant::fromValue<Type>(value());
}

template <typename Type, typename SuperClass>
bool ValueProperty<Type, SuperClass>::fromVariant(const Variant & variant)
{
    if (!variant.canConvert<Type>())
        return false;

    setValue(variant.value<Type>());
    return true;
}

template <typename Type, typename SuperClass>
void ValueProperty<Type, SuperClass>::setAccessors(
    const std::function<Type()> & getter,
    const std::function<void(const Type &)> & setter)
{
    m_getter = getter;
    m_setter = setter;
}

template <typename Type, typename SuperClass>
template <class Object>
void ValueProperty<Type, SuperClass>::setAccessors(
    Object * object,
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
{
    m_getter = std::bind(getter_pointer, object);
    m_setter = std::bind(setter_pointer, object, std::placeholders::_1);
}

template <typename Type, typename SuperClass>
template <class Object>
void ValueProperty<Type, SuperClass>::setAccessors(
    Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
{
    m_getter = std::bind(getter_pointer, object);
    m_setter = std::bind(setter_pointer, object, std::placeholders::_1);
}

template <typename Type, typename SuperClass>
template <class Object>
void ValueProperty<Type, SuperClass>::setAccessors(
    Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
{
    m_getter = std::bind(getter_pointer, object);
    m_setter = std::bind(setter_pointer, object, std::placeholders::_1);
}

} // namespace reflectionzeug
