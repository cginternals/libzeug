#pragma once

#include <reflectionzeug/EnumProperty.h>

#include <cassert>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Enum>
template <typename... Arguments>
EnumProperty<Enum>::EnumProperty(Arguments&&... args)
:   ValueProperty<Enum, EnumPropertyInterface>(std::forward<Arguments>(args)...)
{
    this->setStrings(EnumDefaultStrings<Enum>()());
}

template <typename Enum>
EnumProperty<Enum>::~EnumProperty()
{
}
    
template <typename Type>
void EnumProperty<Type>::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);
    
    if (typedVisitor == nullptr)
        return EnumPropertyInterface::accept(visitor);
    
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
void EnumProperty<Enum>::setStrings(const std::map<Enum, std::string> & pairs)
{
    m_stringMap = pairs;

    m_enumMap.clear();

    std::vector<std::string> strings;

    for (const std::pair<Enum, std::string> & pair : pairs)
    {
        assert(m_enumMap.count(pair.second) == 0);
        m_enumMap.insert(std::make_pair(pair.second, pair.first));
        strings.push_back(pair.second);
    }

    this->setOption("strings", strings);
}

} // namespace reflectionzeug
