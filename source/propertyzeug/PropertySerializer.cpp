
#include <propertyzeug/PropertySerializer.h>

#include <iostream>
#include <sstream>

#include <propertyzeug/AbstractProperty.h>
#include <propertyzeug/PropertyGroup.h>

namespace zeug {
    
PropertySerializer::PropertySerializer()
{
}

PropertySerializer::~PropertySerializer()
{
}
    
bool PropertySerializer::serialize(PropertyGroup & group, std::string filePath)
{
    m_fstream.open(filePath, std::ios_base::out);
    
    if (!m_fstream.is_open()) {
        std::cerr << "Could not write to file \"" << filePath << "\"" << std::endl;
        return false;
    }
    
    
    m_currentPath = "";
    
    m_fstream << "[" << group.name() << "]" << std::endl;
    group.forEachValueProperty([this](AbstractProperty & property) {
        this->serializeProperty(property);
    });
    m_fstream << std::endl;
    
    group.forEachSubGroup([this](PropertyGroup & subGroup) {
        m_fstream << "[" << subGroup.name() << "]" << std::endl;
        this->serializeGroup(subGroup);
        m_fstream << std::endl;
    });
    
    m_fstream.close();
    return true;
}
    
void PropertySerializer::serializeProperty(const AbstractProperty & property)
{
    m_fstream << m_currentPath << property.name();
    m_fstream << "=" << property.valueAsString() << std::endl;
}

void PropertySerializer::serializeGroup(const PropertyGroup & group)
{
    group.forEachProperty([this](AbstractProperty & property) {
        if (property.isGroup()) {
            PropertyGroup & subGroup = *property.as<PropertyGroup>();
            this->pushGroupToPath(subGroup);
            this->serializeGroup(subGroup);
            this->popGroupFromPath();
        } else { 
            this->serializeProperty(property);
        }
    });
}

void PropertySerializer::pushGroupToPath(const PropertyGroup & group)
{
    m_previousPath = m_currentPath;
    m_currentPath += group.name() + "/"; 
}

void PropertySerializer::popGroupFromPath()
{
    m_currentPath = m_previousPath;
}

} // namespace
