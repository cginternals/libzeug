
#pragma once


#include <algorithm>
#include <functional>

#include <reflectionzeug/type/AbstractPropertyArray.h>
#include <reflectionzeug/type/ArrayAccessorValue.h>
#include <reflectionzeug/type/ArrayAccessorGetSet.h>
#include <reflectionzeug/type/Property.h>


namespace reflectionzeug
{


// Read/write
template <typename Type, size_t Size>
AbstractPropertyArray<Type, Size>::AbstractPropertyArray(const std::string & name)
: AbstractPropertyValue<std::array<Type, Size>>(name, new ArrayAccessorValue<Type, Size>())
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
AbstractPropertyArray<Type, Size>::AbstractPropertyArray(const std::string & name, const std::array<Type, Size> & value)
: AbstractPropertyValue<std::array<Type, Size>>(name, new ArrayAccessorValue<Type, Size>(value))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
AbstractPropertyArray<Type, Size>::AbstractPropertyArray(
    const std::string & name,
	std::function<Type (size_t)> getter,
    std::function<void(size_t, const Type &)> setter)
: AbstractPropertyValue<std::array<Type, Size>>(name, new ArrayAccessorGetSet<Type, Size>(getter, setter))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
AbstractPropertyArray<Type, Size>::AbstractPropertyArray(
    const std::string & name,
	Object * object,
    const Type & (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
: AbstractPropertyValue<std::array<Type, Size>>(name, new ArrayAccessorGetSet<Type, Size>(getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
AbstractPropertyArray<Type, Size>::AbstractPropertyArray(
    const std::string & name,
	Object * object,
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
: AbstractPropertyValue<std::array<Type, Size>>(name, new ArrayAccessorGetSet<Type, Size>(getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
AbstractPropertyArray<Type, Size>::AbstractPropertyArray(
    const std::string & name,
	Object * object,
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, Type))
: AbstractPropertyValue<std::array<Type, Size>>(name, new ArrayAccessorGetSet<Type, Size>(getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
AbstractPropertyArray<Type, Size>::AbstractPropertyArray(const std::string & name, ArrayAccessor<Type, Size> * accessor)
: AbstractPropertyValue<std::array<Type, Size>>(name, accessor)
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
AbstractPropertyArray<Type, Size>::~AbstractPropertyArray()
{
    // Destroy accessor values
    for (Property<Type> * prop : m_elements) {
        delete prop;
    }
}

template <typename Type, size_t Size>
bool AbstractPropertyArray<Type, Size>::isEmpty() const
{
    return (Size == 0);
}

template <typename Type, size_t Size>
size_t AbstractPropertyArray<Type, Size>::count() const
{
    return Size;
}

template <typename Type, size_t Size>
AbstractProperty * AbstractPropertyArray<Type, Size>::at(size_t i)
{
    return m_elements.at(i);
}

template <typename Type, size_t Size>
const AbstractProperty * AbstractPropertyArray<Type, Size>::at(size_t i) const
{
    return m_elements.at(i);
}


template <typename Type, size_t Size>
int AbstractPropertyArray<Type, Size>::indexOf(const AbstractProperty * prop) const
{
    // Find element
    auto it = std::find(m_elements.begin(), m_elements.end(), prop);
    if (it == m_elements.end()) {
        // Not found!
        return -1;
    } else {
        // Return index of element
        return (int)std::distance(m_elements.begin(), it);
    }

}

template <typename Type, size_t Size>
void AbstractPropertyArray<Type, Size>::forEach(const std::function<void(AbstractProperty &)> & callback)
{
    for (AbstractProperty * prop : m_elements) {
        callback(*prop);
    }
}


template <typename Type, size_t Size>
void AbstractPropertyArray<Type, Size>::forEach(const std::function<void(const AbstractProperty &)> & callback) const
{
    for (const AbstractProperty * prop : m_elements) {
        callback(*prop);
    }
}

template <typename Type, size_t Size>
Type AbstractPropertyArray<Type, Size>::getElement(size_t i) const
{
    return m_arrayAccessor->getElement(i);
}

template <typename Type, size_t Size>
void AbstractPropertyArray<Type, Size>::setElement(size_t i, const Type & value)
{
    m_arrayAccessor->setElement(i, value);
    this->valueChanged(this->value());
    this->changed();
}

template <typename Type, size_t Size>
void AbstractPropertyArray<Type, Size>::init()
{
    // Create typed value for each element
    for (size_t i = 0; i < Size; ++i)
    {
        this->m_elements[i] = new Property<Type>("_" + std::to_string(i),
                                                 std::bind(&AbstractPropertyArray::getElement, this, i),
                                                 std::bind(&AbstractPropertyArray::setElement, this, i, std::placeholders::_1));
    }
}


// Read-only
template <typename Type, size_t Size>
AbstractPropertyArray<const Type, Size>::AbstractPropertyArray(const std::string & name)
: AbstractPropertyArray<Type, Size>(name, new ArrayAccessorValue<const Type, Size>())
{
}

template <typename Type, size_t Size>
AbstractPropertyArray<const Type, Size>::AbstractPropertyArray(const std::string & name, const std::array<Type, Size> & value)
: AbstractPropertyArray<Type, Size>(name, new ArrayAccessorValue<const Type, Size>(value))
{
}

template <typename Type, size_t Size>
AbstractPropertyArray<const Type, Size>::AbstractPropertyArray(
    const std::string & name,
    std::function<Type (size_t)> getter)
: AbstractPropertyArray<Type, Size>(name, new ArrayAccessorGetSet<const Type, Size>(getter))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractPropertyArray<const Type, Size>::AbstractPropertyArray(
    const std::string & name,
    Object * object,
    const Type & (Object::*getter_pointer)(size_t) const)
: AbstractPropertyArray<Type, Size>(name, new ArrayAccessorGetSet<const Type, Size>(getter_pointer))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractPropertyArray<const Type, Size>::AbstractPropertyArray(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)(size_t) const)
: AbstractPropertyArray<Type, Size>(name, new ArrayAccessorGetSet<const Type, Size>(getter_pointer))
{
}

template <typename Type, size_t Size>
AbstractPropertyArray<const Type, Size>::AbstractPropertyArray(const std::string & name, ArrayAccessor<const Type, Size> * accessor)
: AbstractPropertyArray<Type, Size>(name, accessor)
{
}

template <typename Type, size_t Size>
AbstractPropertyArray<const Type, Size>::~AbstractPropertyArray()
{
}


} // namespace reflectionzeug
