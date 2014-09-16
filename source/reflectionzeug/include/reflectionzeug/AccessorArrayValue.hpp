
#pragma once

#include <reflectionzeug/AccessorArrayValue.h>

namespace reflectionzeug
{

template <typename Type, size_t Size>
AccessorArrayValue<Type, Size>::AccessorArrayValue(
    const std::function<Type (size_t)> & getter,
    const std::function<void(size_t, const Type &)> & setter)
:   m_getter(getter)
,   m_setter(setter)
{

}
    
template <typename Type, size_t Size>
template <class Object>
AccessorArrayValue<Type, Size>::AccessorArrayValue(
    Object * object,
    const Type & (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
:   m_getter(std::bind(getter_pointer, object, std::placeholders::_1))
,   m_setter(std::bind(setter_pointer, object, std::placeholders::_1, std::placeholders::_2))
{
}
    
template <typename Type, size_t Size>
template <class Object>
AccessorArrayValue<Type, Size>::AccessorArrayValue(
    Object * object,
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
:   m_getter(std::bind(getter_pointer, object, std::placeholders::_1))
,   m_setter(std::bind(setter_pointer, object, std::placeholders::_1, std::placeholders::_2))
{
}

template <typename Type, size_t Size>
template <class Object>
AccessorArrayValue<Type, Size>::AccessorArrayValue(
    Object * object,
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, Type))
:   m_getter(std::bind(getter_pointer, object, std::placeholders::_1))
,   m_setter(std::bind(setter_pointer, object, std::placeholders::_1, std::placeholders::_2))
{
}

template <typename Type, size_t Size>
std::array<Type, Size> AccessorArrayValue<Type, Size>::get() const
{
    std::array<Type, Size> array;
    for (size_t i = 0; i < Size; ++i)
        array[i] = m_getter(i);

    return array;
}

template <typename Type, size_t Size>
void AccessorArrayValue<Type, Size>::set(const std::array<Type, Size> & array)
{
    for (size_t i = 0; i < Size; ++i)
        m_setter(i, array[i]);
}

template <typename Type, size_t Size>
Type AccessorArrayValue<Type, Size>::get(size_t i) const
{
    return m_getter(i);
}

template <typename Type, size_t Size>
void AccessorArrayValue<Type, Size>::set(size_t i, const Type & value)
{
    m_setter(i, value);
}

} // namespace reflectionzeug
