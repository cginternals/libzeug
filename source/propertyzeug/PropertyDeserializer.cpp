
#include <iostream>
#include <propertyzeug/Property.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyzeug/PropertyDeserializer.h>

namespace propertyzeug {

PropertySerializer::PropertySerializer()
:   m_rootGroup(nullptr)
,   m_currentGroup(nullptr)
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
    
    bool noErrorsOccured = true;
    m_rootGroup = &group;
    
    for (std::string line; std::getline(m_fstream, line);) {
        if (this->isGroupDeclaration(line))
            noErrorsOccured = this->updateCurrentGroup(line) && noErrorsOccured;
        else if (this->isPropertyDeclaration(line))
            noErrorsOccured = this->setPropertyValue(line) && noErrorsOccured;
    }
    
    return noErrorsOccured;
}
    
bool PropertySerializer::isGroupDeclaration(const std::string line)
{
    static const std::regex groupRegex("\\[" + AbstractProperty::s_nameRegexString + "\\]");

    return std::regex_match(line, groupRegex);
}

bool PropertySerializer::isPropertyDeclaration(const std::string line)
{
    static const std::regex propertyRegex(AbstractProperty::s_nameRegexString +
                                          "(\\/" +
                                          AbstractProperty::s_nameRegexString +
                                          ")*=.+");

    return std::regex_match(line, propertyRegex);
}

bool PropertySerializer::updateCurrentGroup(const std::string line)
{
    std::string groupName = line.substr(1, line.length() - 2);
    
    assert(m_rootGroup);
    if (m_rootGroup->name() == groupName) {
        m_currentGroup = m_rootGroup;
        return true;
    }
    
    if (m_rootGroup->subGroupExists(groupName)) {
        m_currentGroup = &(m_rootGroup->subGroup(groupName));
        return true;
    }
    
    m_currentGroup = nullptr;
    std::cerr << "Group with name \"" << groupName << "\" does not exist" << std::endl;
    return false;
}

bool PropertySerializer::setPropertyValue(const std::string line)
{
    if (!m_currentGroup) {
        std::cerr << "Could not parse line\"" << line << "\" because no existing group was declared" << std::endl;
        return false;
    }

    std::smatch match;
    std::regex_search(line, match, std::regex("="));
    const std::string & path = match.prefix();
    m_currentValue = match.suffix();
    
    PropertyGroup * traverseGroup = m_currentGroup;
    std::regex_search(path, match, std::regex(AbstractProperty::s_nameRegexString));
    for (const std::string & name : match) {
        if (traverseGroup->propertyExists(name)) {
            AbstractProperty & property = traverseGroup->property(name);
            
            if (property.isGroup())
                traverseGroup = property.to<PropertyGroup>();
            else
                property.accept(*this);

        } else {
            std::cerr << "Property/Group with name \"" << name << "\" ";
            std::cerr << "in path \"" << path << "\" not found " << std::endl;
            return false;
        }
    }

    return true;
}


void PropertySerializer::visit(Property<bool> & property)
{
    if (std::regex_match(m_currentValue, std::regex("\\s*true\\s*"))) {
        property.setValue(true);
        return;
    }
    
    if (std::regex_match(m_currentValue, std::regex("\\s*false\\s*"))) {
        property.setValue(false);
    }
}

void PropertySerializer::visit(Property<int> & property)
{
    property.setValue(this->convertString<int>(m_currentValue));
}

void PropertySerializer::visit(Property<unsigned int> & property)
{
    property.setValue(this->convertString<unsigned int>(m_currentValue));
}

void PropertySerializer::visit(Property<long> & property)
{
    property.setValue(this->convertString<long>(m_currentValue));
}

void PropertySerializer::visit(Property<unsigned long> & property)
{
    property.setValue(this->convertString<unsigned long>(m_currentValue));
}

void PropertySerializer::visit(Property<char> & property)
{
    property.setValue(this->convertString<char>(m_currentValue));
}

void PropertySerializer::visit(Property<unsigned char> & property)
{
    property.setValue(this->convertString<unsigned char>(m_currentValue));
}

void PropertySerializer::visit(Property<float> & property)
{
    property.setValue(this->convertString<float>(m_currentValue));
}

void PropertySerializer::visit(Property<double> & property)
{
    property.setValue(this->convertString<double>(m_currentValue));
}

void PropertySerializer::visit(Property<std::string> & property)
{
    property.setValue(m_currentValue);
}

void PropertySerializer::visit(Property<Color> & property)
{
    static const std::string colorRangeRegexString = "([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    static const std::regex colorFormatRegex("\\s*\\(" +
                                colorRangeRegexString + "," +
                                colorRangeRegexString + "," +
                                colorRangeRegexString + "," +
                                colorRangeRegexString +
                                "\\)\\s*");
    
    if (!std::regex_match(m_currentValue, colorFormatRegex)) {
        std::cerr << "Color value has wrong format: " << m_currentValue << std::endl;
        return;
    }
    
    std::smatch match;
    std::regex_search(m_currentValue, match, std::regex(colorRangeRegexString));
    int red, green, blue, alpha;
    red = this->convertString<int>(match[0].str());
    green = this->convertString<int>(match[1].str());
    blue = this->convertString<int>(match[2].str());
    alpha = this->convertString<int>(match[3].str());
    property.setValue(Color(red, green, blue, alpha));
}

void PropertySerializer::visit(Property<FilePath> & property)
{
    property.setValue(m_currentValue);
}

void PropertySerializer::visit(PropertyGroup & property)
{
    /** should not be called **/
}

} // namespace