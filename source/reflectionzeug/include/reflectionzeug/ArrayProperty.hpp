
#pragma once

#include <algorithm>
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
ArrayProperty<Type, Size>::ArrayProperty(const std::array<Type, Size> & array)
:   m_array(new StoredArrayValue<Type, Size>(array))
{
    init();
}

template <typename Type, size_t Size>
ArrayProperty<Type, Size>::ArrayProperty(
    const std::function<Type (size_t)> & getter,
    const std::function<void(size_t, const Type &)> & setter)
:   m_array(new AccessorArrayValue<Type, Size>(getter, setter))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
ArrayProperty<Type, Size>::ArrayProperty(
    Object * object, 
    const Type & (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
:   m_array(new AccessorArrayValue<Type, Size>(object, getter_pointer, setter_pointer))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
ArrayProperty<Type, Size>::ArrayProperty(
    Object * object, 
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, const Type &))
:   m_array(new AccessorArrayValue<Type, Size>(object, getter_pointer, setter_pointer))
{
    init();
}

template <typename Type, size_t Size>
template <class Object>
ArrayProperty<Type, Size>::ArrayProperty(
    Object * object, 
    Type (Object::*getter_pointer)(size_t) const,
    void (Object::*setter_pointer)(size_t, Type))
:   m_array(new AccessorArrayValue<Type, Size>(object, getter_pointer, setter_pointer))
{
    init();
}

template <typename Type, size_t Size>
ArrayProperty<Type, Size>::~ArrayProperty()
{
    for (Property<Type> * property : m_properties)
        delete property;
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<std::array<Type, Size>> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(reinterpret_cast<Property<std::array<Type, Size>> *>(this));
}

template <typename Type, size_t Size>
size_t ArrayProperty<Type, Size>::stype()
{
    static size_t type = typeid(Type).hash_code();
    return type;
}

template <typename Type, size_t Size>
size_t ArrayProperty<Type, Size>::type() const
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
bool ArrayProperty<Type, Size>::isEmpty() const
{
    return false;
}

template <typename Type, size_t Size>
size_t ArrayProperty<Type, Size>::count() const
{
    return Size;
}

template <typename Type, size_t Size>
int ArrayProperty<Type, Size>::indexOf(const AbstractProperty * property) const
{
    auto it = std::find(m_properties.begin(), m_properties.end(), property);

    if (it == m_properties.end())
        return -1;
    
    return std::distance(m_properties.begin(), it);
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
    this->valueChanged(array);
}

template <typename Type, size_t Size>
Type ArrayProperty<Type, Size>::value(size_t i) const
{
    return m_array->get(i);
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::setValue(size_t i, const Type & value)
{
    m_array->set(i, value);
    this->valueChanged(m_array->get());
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::forEach(const std::function<void(Property<Type> &)> & functor)
{
    for (Property<Type> * property : m_properties)
        functor(*property);
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::forEach(const std::function<void(const Property<Type> &)> & functor) const
{
    for (const Property<Type> * property : m_properties)
        functor(*property);
}

template <typename Type, size_t Size>
void ArrayProperty<Type, Size>::init()
{
    for (size_t i = 0; i < Size; ++i)
    {
        m_properties[i] = new Property<Type>("_" + std::to_string(i),
                                             std::bind(&ArrayProperty::value, this, i),
                                             std::bind(&ArrayProperty::setValue, this, i, std::placeholders::_1));
        
        m_properties[i]->setParent(this);
    }
}

} // namespace reflectionzeug
