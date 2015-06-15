
#pragma once


#include <cassert>

#include <reflectionzeug/property/PropertyEnum.h>
#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename Enum>
template <typename... Args>
PropertyEnum<Enum>::PropertyEnum(Args&&... args)
: AbstractPropertyValue<Enum>(std::forward<Args>(args)...)
{
	// Create default enum strings
    this->setStrings(EnumDefaultStrings<Enum>()());
}

template <typename Enum>
PropertyEnum<Enum>::~PropertyEnum()
{
}

template <typename Enum>
std::string PropertyEnum<Enum>::toString() const
{
	// Check if value has a string representation
    assert(m_stringMap.count(this->value()) > 0);

    // Return string representation
    return m_stringMap.at(this->value());
}

template <typename Enum>
bool PropertyEnum<Enum>::fromString(const std::string & string)
{
	// Find enum of string representation
    auto it = m_enumMap.find(string);

    // Abort if it is not available
    if (it == m_enumMap.end())
        return false;

    // Set value
    this->setValue((*it).second);
    return true;
}

template <typename Enum>
std::vector<std::string> PropertyEnum<Enum>::strings() const
{
	// Construct list of all enum strings (without their values)
    std::vector<std::string> strings;
    for (auto element : m_stringMap)
        strings.push_back(element.second);
    return strings;
}

template <typename Enum>
void PropertyEnum<Enum>::setStrings(const std::map<Enum, std::string> & pairs)
{
	// Save map of enum value -> string representation
    m_stringMap = pairs;

    // Construct reverse map (string -> enum value)
    m_enumMap.clear();
    for (const std::pair<Enum, std::string> & pair : pairs)
    {
        assert(m_enumMap.count(pair.second) == 0);
        m_enumMap.insert(std::make_pair(pair.second, pair.first));
    }
}

template <typename Enum>
void PropertyEnum<Enum>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyEnum<Enum>>(this);
    visitor->callVisitor<AbstractEnumInterface>(this);
    visitor->callVisitor<AbstractStringInterface>(this);
}


} // namespace reflectionzeug
