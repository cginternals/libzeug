
#pragma once


#include <reflectionzeug/new/AbstractTypedArray.h>
#include <reflectionzeug/new/ArrayAccessorValue.h>
#include <reflectionzeug/new/ArrayAccessorGetSet.h>


namespace reflectionzeug
{


// Read/write
template <typename Type, size_t Size>
AbstractTypedArray<Type, Size>::AbstractTypedArray()
: AbstractTyped<std::array<Type, Size>>(new ArrayAccessorValue<Type, Size>())
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
}

template <typename Type, size_t Size>
AbstractTypedArray<Type, Size>::AbstractTypedArray(
	std::function<Type (size_t)> getter,
    std::function<void(size_t, const Type &)> setter)
: AbstractTyped<std::array<Type, Size>>(new ArrayAccessorGetSet<Type, Size>(getter, setter))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractTypedArray<Type, Size>::AbstractTypedArray(
	Object * object,
    const Type & (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
: AbstractTyped<std::array<Type, Size>>(new ArrayAccessorGetSet<Type, Size>(getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractTypedArray<Type, Size>::AbstractTypedArray(
	Object * object,
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
: AbstractTyped<std::array<Type, Size>>(new ArrayAccessorGetSet<Type, Size>(getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractTypedArray<Type, Size>::AbstractTypedArray(
	Object * object,
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, Type))
: AbstractTyped<std::array<Type, Size>>(new ArrayAccessorGetSet<Type, Size>(getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
}

template <typename Type, size_t Size>
AbstractTypedArray<Type, Size>::AbstractTypedArray(ArrayAccessor<Type, Size> * accessor)
: AbstractTyped<std::array<Type, Size>>(accessor)
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
}

template <typename Type, size_t Size>
AbstractTypedArray<Type, Size>::~AbstractTypedArray()
{
}


// Read-only
template <typename Type, size_t Size>
AbstractTypedArray<const Type, Size>::AbstractTypedArray()
: AbstractTypedArray<Type, Size>(new ArrayAccessorValue<const Type, Size>())
{
}

template <typename Type, size_t Size>
AbstractTypedArray<const Type, Size>::AbstractTypedArray(
    std::function<Type (size_t)> getter)
: AbstractTypedArray<Type, Size>(new ArrayAccessorGetSet<const Type, Size>(getter))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractTypedArray<const Type, Size>::AbstractTypedArray(
    Object * object,
    const Type & (Object::*getter_pointer)(size_t) const)
: AbstractTypedArray<Type, Size>(new ArrayAccessorGetSet<const Type, Size>(getter_pointer))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractTypedArray<const Type, Size>::AbstractTypedArray(
    Object * object,
    Type (Object::*getter_pointer)(size_t) const)
: AbstractTypedArray<Type, Size>(new ArrayAccessorGetSet<const Type, Size>(getter_pointer))
{
}

template <typename Type, size_t Size>
AbstractTypedArray<const Type, Size>::AbstractTypedArray(ArrayAccessor<const Type, Size> * accessor)
: AbstractTypedArray<Type, Size>(accessor)
{
}

template <typename Type, size_t Size>
AbstractTypedArray<const Type, Size>::~AbstractTypedArray()
{
}


} // namespace reflectionzeug
