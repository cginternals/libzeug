
#pragma once


#include <reflectionzeug/property/AbstractArrayProperty.h>

#include <algorithm>
#include <functional>

#include <reflectionzeug/property/ArrayAccessorGetSet.h>
#include <reflectionzeug/property/ArrayAccessorValue.h>
#include <reflectionzeug/property/Property.h>

#include <stringzeug/manipulation.h>


namespace reflectionzeug
{


// Read/write
template <typename Type, size_t Size>
AbstractArrayProperty<Type, Size>::AbstractArrayProperty(
    const std::string & name,
    std::function<Type (size_t)> getter,
    std::function<void(size_t, const Type &)> setter)
: AbstractTypedProperty<std::array<Type, Size>>(name, new ArrayAccessorGetSet<Type, Size>(getter, setter))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
AbstractArrayProperty<Type, Size>::AbstractArrayProperty(
    const std::string & name,
    Object * object,
    const Type & (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
: AbstractTypedProperty<std::array<Type, Size>>(name, new ArrayAccessorGetSet<Type, Size>(object, getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
AbstractArrayProperty<Type, Size>::AbstractArrayProperty(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
: AbstractTypedProperty<std::array<Type, Size>>(name, new ArrayAccessorGetSet<Type, Size>(object, getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
AbstractArrayProperty<Type, Size>::AbstractArrayProperty(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, Type))
: AbstractTypedProperty<std::array<Type, Size>>(name, new ArrayAccessorGetSet<Type, Size>(object, getter_pointer, setter_pointer))
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
AbstractArrayProperty<Type, Size>::AbstractArrayProperty(const std::string & name, ArrayAccessor<Type, Size> * accessor)
: AbstractTypedProperty<std::array<Type, Size>>(name, accessor)
, m_arrayAccessor(static_cast<ArrayAccessor<Type, Size>*>(this->m_accessor.get()))
{
    init();
}

template <typename Type, size_t Size>
AbstractArrayProperty<Type, Size>::~AbstractArrayProperty()
{
    // Destroy accessor values
    for (Property<Type> * prop : m_elements) {
        delete prop;
    }
}

template <typename Type, size_t Size>
Type AbstractArrayProperty<Type, Size>::getElement(size_t i) const
{
    return m_arrayAccessor->getElement(i);
}

template <typename Type, size_t Size>
void AbstractArrayProperty<Type, Size>::setElement(size_t i, const Type & value)
{
    m_arrayAccessor->setElement(i, value);
    this->valueChanged(this->value());
    this->changed();
}

template <typename Type, size_t Size>
std::string AbstractArrayProperty<Type, Size>::toString() const
{
    std::vector<std::string> stringVector;

    for (size_t i=0; i<Size; i++) {
        stringVector.push_back(at(i)->toString());
    }

    return "(" + stringzeug::join(stringVector, ", ") + ")";
}

template <typename Type, size_t Size>
bool AbstractArrayProperty<Type, Size>::fromString(const std::string & string)
{
    std::vector<std::string> elementStrings = stringzeug::splitArray(string, Size);

    if (elementStrings.size() != Size)
        return false;

    for (size_t i=0; i<Size; i++)
    {
        if (!at(i)->fromString(elementStrings[i]))
            return false;
    }

    return true;
}

template <typename Type, size_t Size>
Variant AbstractArrayProperty<Type, Size>::toVariant() const
{
    Variant value = Variant::array();
    for (size_t i=0; i<Size; i++) {
        value.asArray()->push_back(at(i)->toVariant());
    }
    return value;
}

template <typename Type, size_t Size>
bool AbstractArrayProperty<Type, Size>::fromVariant(const Variant & value)
{
    // Check if variant is an array
    if (!value.isArray()) {
        return false;
    }

    // Get array
    const VariantArray & array = *(value.asArray());
    if (array.size() != Size) {
        return false;
    }

    // Set values
    for (size_t i=0; i<array.size(); i++) {
        const Variant & value = array[i];

        if (!at(i)->fromVariant(value)) {
            return false;
        }
    }

    return true;
}

template <typename Type, size_t Size>
bool AbstractArrayProperty<Type, Size>::isEmpty() const
{
    return (Size == 0);
}

template <typename Type, size_t Size>
size_t AbstractArrayProperty<Type, Size>::count() const
{
    return Size;
}

template <typename Type, size_t Size>
AbstractProperty * AbstractArrayProperty<Type, Size>::at(size_t i)
{
    return m_elements.at(i);
}

template <typename Type, size_t Size>
const AbstractProperty * AbstractArrayProperty<Type, Size>::at(size_t i) const
{
    return m_elements.at(i);
}


template <typename Type, size_t Size>
int AbstractArrayProperty<Type, Size>::indexOf(const AbstractProperty * prop) const
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
void AbstractArrayProperty<Type, Size>::forEach(const std::function<void(AbstractProperty &)> & callback)
{
    for (AbstractProperty * prop : m_elements) {
        callback(*prop);
    }
}


template <typename Type, size_t Size>
void AbstractArrayProperty<Type, Size>::forEach(const std::function<void(const AbstractProperty &)> & callback) const
{
    for (const AbstractProperty * prop : m_elements) {
        callback(*prop);
    }
}

template <typename Type, size_t Size>
void AbstractArrayProperty<Type, Size>::init()
{
    // Create typed value for each element
    for (size_t i = 0; i < Size; ++i)
    {
        this->m_elements[i] = new Property<Type>(
            "_" + std::to_string(i),
            [this, i] () -> Type {
                return AbstractArrayProperty::getElement(i);
            },
            [this, i] (const Type & value) {
                AbstractArrayProperty::setElement(i, value);
            }
        );
    }
}


// Read-only
template <typename Type, size_t Size>
AbstractArrayProperty<const Type, Size>::AbstractArrayProperty(
    const std::string & name,
    std::function<Type (size_t)> getter)
: AbstractArrayProperty<Type, Size>(name, new ArrayAccessorGetSet<const Type, Size>(getter))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractArrayProperty<const Type, Size>::AbstractArrayProperty(
    const std::string & name,
    Object * object,
    const Type & (Object::*getter_pointer)(size_t) const)
: AbstractArrayProperty<Type, Size>(name, new ArrayAccessorGetSet<const Type, Size>(object, getter_pointer))
{
}

template <typename Type, size_t Size>
template <class Object>
AbstractArrayProperty<const Type, Size>::AbstractArrayProperty(
    const std::string & name,
    Object * object,
    Type (Object::*getter_pointer)(size_t) const)
: AbstractArrayProperty<Type, Size>(name, new ArrayAccessorGetSet<const Type, Size>(object, getter_pointer))
{
}

template <typename Type, size_t Size>
AbstractArrayProperty<const Type, Size>::AbstractArrayProperty(const std::string & name, ArrayAccessor<const Type, Size> * accessor)
: AbstractArrayProperty<Type, Size>(name, accessor)
{
}

template <typename Type, size_t Size>
AbstractArrayProperty<const Type, Size>::~AbstractArrayProperty()
{
}


} // namespace reflectionzeug
