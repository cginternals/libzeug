
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

template <typename Type, size_t Size>
bool AbstractTypedArray<Type, Size>::isEmpty() const
{
    return (Size == 0);
}

template <typename Type, size_t Size>
size_t AbstractTypedArray<Type, Size>::count() const
{
    return Size;
}

template <typename Type, size_t Size>
AbstractValue * AbstractTypedArray<Type, Size>::at(size_t i)
{
    // [TODO]
    return nullptr;
}

template <typename Type, size_t Size>
const AbstractValue * AbstractTypedArray<Type, Size>::at(size_t i) const
{
    // [TODO]
    return nullptr;
}


template <typename Type, size_t Size>
int AbstractTypedArray<Type, Size>::indexOf(const AbstractValue * value) const
{
    // [TODO]
    return 0;
}


template <typename Type, size_t Size>
void AbstractTypedArray<Type, Size>::forEach(const std::function<void(AbstractValue &)> & callback)
{
    // [TODO]
}


template <typename Type, size_t Size>
void AbstractTypedArray<Type, Size>::forEach(const std::function<void(const AbstractValue &)> & callback) const
{
    // [TODO]
}

template <typename Type, size_t Size>
Type AbstractTypedArray<Type, Size>::getElement(size_t i) const
{
    return m_arrayAccessor->getElement(i);
}

template <typename Type, size_t Size>
void AbstractTypedArray<Type, Size>::setElement(size_t i, const Type & value)
{
    m_arrayAccessor->setElement(i, value);
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
