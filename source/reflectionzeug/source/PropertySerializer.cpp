

#include <iostream>
#include <sstream>

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/PropertyGroup.h>

#include <reflectionzeug/PropertySerializer.h>

namespace reflectionzeug
{
    
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
    group.forEachValue([this] (AbstractValueProperty & property) 
        {
            this->serializeValue(property);
        });
    m_fstream << std::endl;
    
    group.forEachGroup([this](PropertyGroup & subGroup) 
        {
            m_fstream << "[" << subGroup.name() << "]" << std::endl;
            this->serializeGroup(subGroup);
            m_fstream << std::endl;
        });
    
    m_fstream.close();
    return true;
}
    
void PropertySerializer::serializeValue(const AbstractValueProperty & property)
{
    m_fstream << m_currentPath << property.name();
    m_fstream << "=" << property.toString() << std::endl;
}

void PropertySerializer::serializeGroup(const PropertyGroup & group)
{
    group.forEach([this] (const AbstractProperty & property) {
        if (property.isGroup()) {
            const PropertyGroup & subGroup = *property.asGroup();
            this->pushGroupToPath(subGroup);
            this->serializeGroup(subGroup);
            this->popGroupFromPath();
        } else { 
            this->serializeValue(*property.asValue());
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

} // namespace reflectionzeug
