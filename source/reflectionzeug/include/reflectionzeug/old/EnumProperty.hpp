#pragma once

#include <reflectionzeug/EnumProperty.h>

#include <cassert>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Enum>
EnumProperty<Enum>::EnumProperty()
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
    EnumPropertyInterface::accept(visitor);
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
bool EnumProperty<Enum>::hasChoices() const
{
    return !m_choices.empty();
}

template <typename Enum>
const std::vector<Enum> & EnumProperty<Enum>::choices() const
{
    return m_choices;
}

template <typename Enum>
void EnumProperty<Enum>::setChoices(const std::vector<Enum> & choices)
{
    m_choices = choices;
}

template <typename Enum>
std::vector<std::string> EnumProperty<Enum>::choicesStrings() const
{
    std::vector<std::string> strings;
    for (auto choice : m_choices)
        strings.push_back(m_stringMap.at(choice));
    return strings;
}

template <typename Enum>
std::vector<std::string> EnumProperty<Enum>::strings() const
{
    std::vector<std::string> strings;
    for (auto element : m_stringMap)
        strings.push_back(element.second);
    return strings;
}

template <typename Enum>
void EnumProperty<Enum>::setStrings(const std::map<Enum, std::string> & pairs)
{
    m_stringMap = pairs;
    m_enumMap.clear();

    for (const std::pair<Enum, std::string> & pair : pairs)
    {
        assert(m_enumMap.count(pair.second) == 0);
        m_enumMap.insert(std::make_pair(pair.second, pair.first));
    }
}

} // namespace reflectionzeug
