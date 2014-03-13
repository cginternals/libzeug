
#pragma once

#include <cassert>

namespace reflectionzeug
{

template <typename Enum>
EnumProperty<Enum>::EnumProperty(const std::string & name, const Enum & value)
:   ValuePropertyInterface(name)
,   EnumPropertyInterface(name)
,   ValueProperty<Enum>(name, value)
,   m_isInitialized(false)
{
}

template <typename Enum>
EnumProperty<Enum>::EnumProperty(const std::string & name,
    const std::function<Enum ()> & getter,
    const std::function<void(const Enum &)> & setter)
:   ValuePropertyInterface(name)
,   EnumPropertyInterface(name)
,   ValueProperty<Enum>(name, getter, setter)
,   m_isInitialized(false)
{
}

template <typename Enum>
template <class Object>
EnumProperty<Enum>::EnumProperty(const std::string & name,
    Object & object, const Enum & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Enum &))
:   ValuePropertyInterface(name)
,   EnumPropertyInterface(name)
,   ValueProperty<Enum>(name, object, getter_pointer, setter_pointer)
,   m_isInitialized(false)
{
}

template <typename Enum>
template <class Object>
EnumProperty<Enum>::EnumProperty(const std::string & name,
    Object & object, Enum (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Enum &))
:   ValuePropertyInterface(name)
,   EnumPropertyInterface(name)
,   ValueProperty<Enum>(name, object, getter_pointer, setter_pointer)
,   m_isInitialized(false)
{
}

template <typename Enum>
template <class Object>
EnumProperty<Enum>::EnumProperty(const std::string & name,
    Object & object, Enum (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Enum))
:   ValuePropertyInterface(name)
,   EnumPropertyInterface(name)
,   ValueProperty<Enum>(name, object, getter_pointer, setter_pointer)
,   m_isInitialized(false)
{
}

template <typename Enum>
std::string EnumProperty<Enum>::toString() const
{
    if (!m_isInitialized) init();

    assert(m_stringMap.count(this->value()) > 0);

    return m_stringMap.at(this->value());
}

template <typename Enum>
bool EnumProperty<Enum>::fromString(const std::string & string)
{
    if (!m_isInitialized) init();

    auto it = m_enumMap.find(string);

    if (it == m_enumMap.end())
        return false;

    this->setValue((*it).second);
    return true;
}

template <typename Enum>
const std::vector<std::string> & EnumProperty<Enum>::stringList() const
{
    if (!m_isInitialized) init();

    return m_stringList;
}

template <typename Enum>
void EnumProperty<Enum>::init() const
{
    auto * that = const_cast<EnumProperty<Enum> *>(this);
    
    for (const std::pair<Enum, std::string> & pair : pairs())
    {
        {
            auto result = that->m_stringMap.insert(pair);
            assert(result.second);
        }
        {
            auto result = that->m_enumMap.insert(std::make_pair(pair.second, pair.first));
            assert(result.second);
        }

        that->m_stringList.push_back(pair.second);
    }

    that->m_isInitialized = true;
}

template <typename Type>
void EnumProperty<Type>::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);

    if (typedVisitor == nullptr)
    {
        EnumPropertyInterface::accept(visitor, warn);
        return;
    }

    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

} // namespace reflectionzeug
