
#pragma once

#include <cassert>

namespace reflectionzeug
{

template <typename Enum>
EnumProperty<Enum>::EnumProperty(const Enum & value)
:   ValueProperty<Enum>(value)
{
}

template <typename Enum>
EnumProperty<Enum>::EnumProperty(
    const std::function<Enum ()> & getter,
    const std::function<void(const Enum &)> & setter)
:   ValueProperty<Enum>(getter, setter)
{
}

template <typename Enum>
template <class Object>
EnumProperty<Enum>::EnumProperty(
    Object & object, 
    const Enum & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Enum &))
:   ValueProperty<Enum>(object, getter_pointer, setter_pointer)
{
}

template <typename Enum>
template <class Object>
EnumProperty<Enum>::EnumProperty(
    Object & object, 
    Enum (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Enum &))
:   ValueProperty<Enum>(object, getter_pointer, setter_pointer)
{
}

template <typename Enum>
template <class Object>
EnumProperty<Enum>::EnumProperty(
    Object & object, 
    Enum (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Enum))
:   ValueProperty<Enum>(object, getter_pointer, setter_pointer)
{
}

template <typename Enum>
EnumProperty<Enum>::~EnumProperty()
{
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

template <typename Enum>
std::string EnumProperty<Enum>::toString() const
{
    assert(m_stringMap.count(this->value()) > 0);

    return m_stringMap.at(this->value());
}

template <typename Enum>
bool EnumProperty<Enum>::fromString(const std::string & string)
{
    auto it = m_enumMap.find(string);

    if (it == m_enumMap.end())
        return false;

    this->setValue((*it).second);
    return true;
}
    
template <typename Enum>
std::vector<std::string> EnumProperty<Enum>::strings() const
{
    std::vector<std::string> strings;
    for (const std::pair<Enum, std::string> & pair : m_stringMap)
    {
        strings.push_back(pair.second);
    }
    
    return strings;
}
    
template <typename Enum>
void EnumProperty<Enum>::setStrings(const std::vector<std::pair<Enum, std::string>> & pairs)
{
    m_stringMap.clear();
    m_enumMap.clear();
    
    for (const std::pair<Enum, std::string> & pair : pairs)
    {
        assert(m_stringMap.count(pair.first) == 0);
        m_stringMap.emplace(pair.first, pair.second);
        
        assert(m_enumMap.count(pair.second) == 0);
        m_enumMap.emplace(pair.second, pair.first);
    }
}

} // namespace reflectionzeug
