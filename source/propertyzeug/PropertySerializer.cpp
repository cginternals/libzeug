
#include <iostream>
#include <sstream>
#include <propertyzeug/Property.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyzeug/PropertySerializer.h>

namespace propertyzeug {
    
const std::regex PropertySerializer::s_groupRegex("\\[[a-zA-Z]\\w*\\]");
const std::regex PropertySerializer::s_propertyRegex("[a-zA-Z]\\w*(\\/[a-zA-Z]\\w*)*=.+");

PropertySerializer::PropertySerializer()
:   m_currentGroup(nullptr)
,   m_currentValue("")
{
}

PropertySerializer::~PropertySerializer()
{
}

bool PropertySerializer::serialize(PropertyGroup & group, std::string filePath)
{
    
    return false;
}

bool PropertySerializer::deserialize(PropertyGroup & group, std::string filePath)
{
    m_fstream.open(filePath, std::ios_base::in);
    if (!m_fstream.is_open()) {
        std::cerr << "Could not open file \"" << filePath << "\"" << std::endl;
        return false;
    }
    
    for (std::string line; std::getline(m_fstream, line);) {
        if (std::regex_match(line, s_groupRegex)) {
            std::string groupName = line.substr(1, line.length() - 2);
            
            if (group.name().compare(groupName)) {
                m_currentGroup = &group;
            } else {
                if (group.propertyExists(groupName))
                    m_currentGroup = &group.subGroup(groupName);
                else
                    std::cerr << "Group with name \"" << groupName << "\" does not exist";
            }
        } else if (std::regex_match(line, s_propertyRegex)) {
            std::smatch match;
            std::regex_search(line, match, std::regex("="));
            const std::string & path = match.prefix();
            m_currentValue = match.suffix();
            
            std::regex_search(path, match, AbstractProperty::s_nameRegex);
            PropertyGroup * traverse_group = m_currentGroup;
            for (const std::string & name : match) {
                if (traverse_group->propertyExists(name)) {
                    AbstractProperty & property = traverse_group->property(name);
                    if (property.isGroup()) {
                        traverse_group = property.to<PropertyGroup>();
                    } else {
                        property.accept(*this);
                    }
                } else {
                    std::cerr << "Something went wrong" << std::endl;
                }
                
            }
        }
    }
    
    return true;
} 

void PropertySerializer::visit(Property<bool> & property)
{

}

void PropertySerializer::visit(Property<int> & property)
{
    std::stringstream stream(m_currentValue);
    int value;
    stream >> value;
    property.setValue(value);
}

void PropertySerializer::visit(Property<unsigned int> & property)
{

}

void PropertySerializer::visit(Property<long> & property)
{

}

void PropertySerializer::visit(Property<unsigned long> & property)
{

}

void PropertySerializer::visit(Property<char> & property)
{

}

void PropertySerializer::visit(Property<unsigned char> & property)
{

}

void PropertySerializer::visit(Property<float> & property)
{

}

void PropertySerializer::visit(Property<double> & property)
{

}

void PropertySerializer::visit(Property<std::string> & property)
{

}

void PropertySerializer::visit(Property<Color> & property)
{

}

void PropertySerializer::visit(Property<FilePath> & property)
{

}

void PropertySerializer::visit(PropertyGroup & property)
{

}

} // namespace