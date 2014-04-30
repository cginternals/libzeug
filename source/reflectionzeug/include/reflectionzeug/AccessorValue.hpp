
#pragma once

namespace reflectionzeug
{

template <typename Type>
AccessorValue<Type>::AccessorValue(std::function<Type ()> getter,
    std::function<void(const Type &)> setter)
:   m_getter(getter)
,   m_setter(setter)
{   
}
    
template <typename Type>
template <class Object>
AccessorValue<Type>::AccessorValue(Object * object,
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   m_getter(std::bind(getter_pointer, object))
,   m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}
    
template <typename Type>
template <class Object>
AccessorValue<Type>::AccessorValue(Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   m_getter(std::bind(getter_pointer, object))
,   m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}

template <typename Type>
template <class Object>
AccessorValue<Type>::AccessorValue(Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   m_getter(std::bind(getter_pointer, object))
,   m_setter(std::bind(setter_pointer, object, std::placeholders::_1))
{
}

template <typename Type>
AccessorValue<Type>::~AccessorValue()
{
}

template <typename Type>
Type AccessorValue<Type>::get() const
{
    return m_getter();
}

template <typename Type>
void AccessorValue<Type>::set(const Type & value)
{
    m_setter(value);
}

} // namespace reflectionzeug
