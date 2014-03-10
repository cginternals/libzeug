
#pragma once

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Type>
ValueProperty<Type>::ValueProperty(const std::string & name,
    const Type & value)
:   ValuePropertyInterface(name)
,   m_value(new StoredValue<Type>(value))
{
}

template <typename Type>
ValueProperty<Type>::ValueProperty(const std::string & name, 
    const std::function<Type ()> & getter,
    const std::function<void(const Type &)> & setter)
:   ValuePropertyInterface(name)
,   m_value(new AccessorValue<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValuePropertyInterface(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValuePropertyInterface(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   ValuePropertyInterface(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
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
void ValueProperty<Type>::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);

    if (typedVisitor == nullptr)
    {
        ValuePropertyInterface::accept(visitor, warn);
        return;
    }

    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

} // namespace reflectionzeug
