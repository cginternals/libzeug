
#pragma once


#include <algorithm>
#include <functional>

#include <reflectionzeug/new/AbstractTypedArray.h>
#include <reflectionzeug/new/ArrayAccessorValue.h>
#include <reflectionzeug/new/ArrayAccessorGetSet.h>
#include <reflectionzeug/new/NamedTyped.h>


namespace reflectionzeug
{


// Read/write
template <typename Type, size_t Size>
AbstractTypedArray<Type, Size>::AbstractTypedArray()
: AbstractTyped<std::array<Type, Size>>(new ArrayAccessorValue<Type, Size>())
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
AbstractTypedArray<Type, Size>::AbstractTypedArray(
	std::function<Type (size_t)> getter,
    std::function<void(size_t, const Type &)> setter)
: AbstractTyped<std::array<Type, Size>>(new ArrayAccessorGetSet<Type, Size>(getter, setter))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
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
    init();
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
    init();
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
    init();
}

template <typename Type, size_t Size>
AbstractTypedArray<Type, Size>::AbstractTypedArray(ArrayAccessor<Type, Size> * accessor)
: AbstractTyped<std::array<Type, Size>>(accessor)
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
AbstractTypedArray<Type, Size>::~AbstractTypedArray()
{
    // Destroy accessor values
    for (Typed<Type> * typed : m_elements) {
        delete typed;
    }
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
    return m_elements.at(i);
}

template <typename Type, size_t Size>
const AbstractValue * AbstractTypedArray<Type, Size>::at(size_t i) const
{
    return m_elements.at(i);
}


template <typename Type, size_t Size>
int AbstractTypedArray<Type, Size>::indexOf(const AbstractValue * value) const
{
    // Find element
    auto it = std::find(m_elements.begin(), m_elements.end(), value);
    if (it == m_elements.end()) {
        // Not found!
        return -1;
    } else {
        // Return index of element
        return (int)std::distance(m_elements.begin(), it);
    }

}

template <typename Type, size_t Size>
void AbstractTypedArray<Type, Size>::forEach(const std::function<void(AbstractValue &)> & callback)
{
    for (AbstractValue * value : m_elements) {
        callback(*value);
    }
}


template <typename Type, size_t Size>
void AbstractTypedArray<Type, Size>::forEach(const std::function<void(const AbstractValue &)> & callback) const
{
    for (const AbstractValue * value : m_elements) {
        callback(*value);
    }
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
    this->valueChanged();
}

template <typename Type, size_t Size>
void AbstractTypedArray<Type, Size>::init()
{
    // Create typed value for each element
    for (size_t i = 0; i < Size; ++i)
    {
        this->m_elements[i] = new NamedTyped<Type>("_" + std::to_string(i),
                                                   std::bind(&AbstractTypedArray::getElement, this, i),
                                                   std::bind(&AbstractTypedArray::setElement, this, i, std::placeholders::_1));
    }
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
