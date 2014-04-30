
#pragma once

#include <typeinfo>

#include <reflectionzeug/PropertyVisitor.h>
#include <reflectionzeug/StoredValue.h>
#include <reflectionzeug/AccessorValue.h>

namespace reflectionzeug
{

template <typename Type>
ValueProperty<Type>::ValueProperty(const Type & value)
:   m_value(new StoredValue<Type>(value))
{
}

template <typename Type>
ValueProperty<Type>::ValueProperty(
    const std::function<Type ()> & getter,
    const std::function<void(const Type &)> & setter)
:   m_value(new AccessorValue<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(
    Object * object, 
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(
    Object * object, 
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(
    Object * object, 
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
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
    this->valueChanged(value);
}

template <typename Type>
void ValueProperty<Type>::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
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

} // namespace reflectionzeug
