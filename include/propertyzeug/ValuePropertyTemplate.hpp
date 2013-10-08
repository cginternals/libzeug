
#pragma once

namespace zeug {

template <typename Type>
ValuePropertyTemplate<Type>::ValuePropertyTemplate(const std::string & name,
    const Type & value)
:   ValueProperty(name)
,   m_value(new StoredValue<Type>(value))
{
}

template <typename Type>
ValuePropertyTemplate<Type>::ValuePropertyTemplate(const std::string & name, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   ValueProperty(name)
,   m_value(new AccessorValue<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
ValuePropertyTemplate<Type>::ValuePropertyTemplate(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValueProperty(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
ValuePropertyTemplate<Type>::ValuePropertyTemplate(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValueProperty(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}

template <typename Type>
ValuePropertyTemplate<Type>::~ValuePropertyTemplate()
{
}

template <typename Type>
const Type & ValuePropertyTemplate<Type>::value() const
{
    return m_value->get();
}

template <typename Type>
void ValuePropertyTemplate<Type>::setValue(const Type & value)
{
    m_value->set(value);
    this->valueChanged(value);
}

} // namespace zeug
