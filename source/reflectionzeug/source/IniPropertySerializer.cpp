#include <reflectionzeug/IniPropertySerializer.h>

#include <sstream>
#include <iostream>

#include <loggingzeug/logging.h>

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/util.h>

using namespace loggingzeug;

namespace reflectionzeug
{
    
IniPropertySerializer::IniPropertySerializer()
{
}

IniPropertySerializer::~IniPropertySerializer()
{
}
    
bool IniPropertySerializer::serialize(PropertyGroup & group, const std::string & filePath)
{
    m_fstream.open(filePath, std::ios_base::out);
    
    if (!m_fstream.is_open()) {
        critical() << "Could not write to file \"" << filePath << "\"" << std::endl;
        return false;
    }

    m_pathStack.clear();
    
    m_fstream << "[" << group.name() << "]" << std::endl;
    group.forEachValue(
        [this] (AbstractValueProperty & property) 
        {
            this->serializeValue(property);
        });
    m_fstream << std::endl;
    
    group.forEachGroup(
        [this](PropertyGroup & subGroup) 
        {
            m_fstream << "[" << subGroup.name() << "]" << std::endl;
            this->serializeGroup(subGroup);
            m_fstream << std::endl;
        });
    
    m_fstream.close();
    return true;
}
    
void IniPropertySerializer::serializeValue(const AbstractValueProperty & property)
{
    m_fstream << currentPath() << property.name();
    m_fstream << "=" << property.toString() << std::endl;
}

void IniPropertySerializer::serializeGroup(const PropertyGroup & group)
{
    group.forEach(
        [this] (const AbstractProperty & property) 
        {
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

void IniPropertySerializer::pushGroupToPath(const PropertyGroup & group)
{
    m_pathStack.push_back(group.name());
}

void IniPropertySerializer::popGroupFromPath()
{
    m_pathStack.pop_back();
}

std::string IniPropertySerializer::currentPath() const
{
    std::stringstream stream;

    for (const std::string & name : m_pathStack)
        stream << name << "/";

    return stream.str();
}

} // namespace reflectionzeug
