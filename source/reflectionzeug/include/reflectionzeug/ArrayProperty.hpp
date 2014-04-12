
#pragma once

#include <cassert>
#include <iostream>
#include <typeinfo>
#include <vector>

#include <reflectionzeug/Property.h>
#include <reflectionzeug/AccessorArrayValue.h>
#include <reflectionzeug/StoredArrayValue.h>
#include <reflectionzeug/PropertyVisitor.h>
#include <reflectionzeug/util.h>


namespace reflectionzeug
{

template <typename Type, size_t Size>
ArrayProperty<Type, Size>::ArrayProperty(
    const std::string & name, 
    const std::array<Type, Size> & array)
:   ArrayPropertyInterface(name)
,   m_array(new StoredArrayValue<Type, Size>(array))
{
    init();
}

template <typename Type, size_t Size>
ArrayProperty<Type, Size>::ArrayProperty(
    const std::string & name,
    const std::function<Type (size_t)> & getter,
    const std::function<void(size_t, const Type &)> & setter)
:   ArrayPropertyInterface(name)
,   m_array(new AccessorArrayValue<Type, Size>(getter, setter))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
ArrayProperty<Type, Size>::ArrayProperty(
    const std::string & name,
    Object & object, 
    const Type & (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
:   ArrayPropertyInterface(name)
,   m_array(new AccessorArrayValue<Type, Size>(object, getter_pointer, setter_pointer))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
ArrayProperty<Type, Size>::ArrayProperty(
    const std::string & name,
    Object & object, 
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
:   m_array(new AccessorArrayValue<Type, Size>(object, getter_pointer, setter_pointer))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
ArrayProperty<Type, Size>::ArrayProperty(
    const std::string & name,
    Object & object, 
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, Type))
:   ArrayPropertyInterface(name)
,   m_array(new AccessorArrayValue<Type, Size>(object, getter_pointer, setter_pointer))
{
    init();
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<std::array<Type, Size>> *>(visitor);

    if (typedVisitor == nullptr)
    {
        ValuePropertyInterface::accept(visitor, warn);
        return;
    }

    typedVisitor->visit(reinterpret_cast<Property<std::array<Type, Size>> *>(this));
}

template <typename Type, size_t Size>
size_t ArrayProperty<Type, Size>::stype()
{
    static size_t type = typeid(Type).hash_code();
    return type;
}

template <typename Type, size_t Size>
size_t ArrayProperty<Type, Size>::type()
{
    return stype();
}

template <typename Type, size_t Size>
std::string ArrayProperty<Type, Size>::toString() const
{
    std::vector<std::string> stringVector;
    
    for (Property<Type> * property : m_properties)
        stringVector.push_back(property->toString());

    return "(" + util::join(stringVector, ", ") + ")";
}

template <typename Type, size_t Size>
bool ArrayProperty<Type, Size>::fromString(const std::string & string)
{
    std::vector<std::string> elementStrings = util::splitArray(Size, string);

    if (elementStrings.size() != Size)
        return false;

    for (size_t i = 0; i < Size; ++i)
    {
        if (!m_properties[i]->fromString(elementStrings[i]))
            return false;
    }

    return true;
}

template <typename Type, size_t Size>
ArrayProperty<Type, Size>::~ArrayProperty()
{
    for (Property<Type> * property : m_properties)
        delete property;
}

template <typename Type, size_t Size>
std::array<Type, Size> ArrayProperty<Type, Size>::array() const
{
    return m_array->get();
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::setArray(const std::array<Type, Size> & array)
{
    m_array->set(array);
}

template <typename Type, size_t Size>
Type ArrayProperty<Type, Size>::value(size_t i) const
{
    return m_array->get(i);
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::setValue(size_t i, const Type & value)
{
    return m_array->set(i, value);
}

template <typename Type, size_t Size>
size_t ArrayProperty<Type, Size>::size() const
{
    return Size;
}

template <typename Type, size_t Size>
Property<Type> * ArrayProperty<Type, Size>::at(size_t i)
{
    return m_properties.at(i);
}

template <typename Type, size_t Size>
const Property<Type> * ArrayProperty<Type, Size>::at(size_t i) const
{
    return m_properties.at(i);
}

template <typename Type, size_t Size>
const std::array<Property<Type> *, Size> & ArrayProperty<Type, Size>::subProperties()
{
    return m_properties;
}

template <typename Type, size_t Size>
const std::array<const Property<Type> *, Size> & ArrayProperty<Type, Size>::subProperties() const
{
    return m_properties;
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::init()
{
    for (size_t i = 0; i < Size; ++i)
    {
        m_properties[i] = new Property<Type>("_" + std::to_string(i),
                                             std::bind(&ArrayProperty::value, this, i),
                                             std::bind(&ArrayProperty::setValue, this, i, std::placeholders::_1));
    }
}

} // namespace reflectionzeug
