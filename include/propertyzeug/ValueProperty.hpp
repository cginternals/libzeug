
#pragma once

namespace zeug {

template <typename Type>
ValueProperty<Type>::ValueProperty(const std::string & name,
    const Type & value)
:   AbstractProperty(name)
,   m_value(new StoredValue<Type>(value))
{
}

template <typename Type>
ValueProperty<Type>::ValueProperty(const std::string & name, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}

template <typename Type>
ValueProperty<Type>::~ValueProperty()
{
}

template <typename Type>
const Type & ValueProperty<Type>::value() const
{
    return m_value->get();
}

template <typename Type>
void ValueProperty<Type>::setValue(const Type & value)
{
    m_value->set(value);
    this->valueChanged(value);
}

} // namespace zeug
