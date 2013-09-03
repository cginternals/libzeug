
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <propertyzeug/Property.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyzeug/PropertyDeserializer.h>

namespace propertyzeug {

PropertyDeserializer::PropertyDeserializer()
:   m_rootGroup(nullptr)
,   m_currentGroup(nullptr)
,   m_currentValue("")
{
}

PropertyDeserializer::~PropertyDeserializer()
{
}

bool PropertyDeserializer::deserialize(PropertyGroup & group, std::string filePath)
{
    std::fstream fstream;
    fstream.open(filePath, std::ios_base::in);
    if (!fstream.is_open()) {
        std::cerr << "Could not open file \"" << filePath << "\"" << std::endl;
        return false;
    }
    
    bool noErrorsOccured = true;
    m_rootGroup = &group;
    
    for (std::string line; std::getline(fstream, line);) {
        if (this->isGroupDeclaration(line))
            noErrorsOccured = this->updateCurrentGroup(line) && noErrorsOccured;
        else if (this->isPropertyDeclaration(line))
            noErrorsOccured = this->setPropertyValue(line) && noErrorsOccured;
    }

    fstream.close();
    return noErrorsOccured;
}
    
bool PropertyDeserializer::isGroupDeclaration(const std::string line)
{
    static const std::regex groupRegex("\\[" + AbstractProperty::s_nameRegexString + "\\]");

    return std::regex_match(line, groupRegex);
}

bool PropertyDeserializer::isPropertyDeclaration(const std::string line)
{
    static const std::regex propertyRegex(AbstractProperty::s_nameRegexString +
                                          "(\\/" +
                                          AbstractProperty::s_nameRegexString +
                                          ")*=.+");

    return std::regex_match(line, propertyRegex);
}

bool PropertyDeserializer::updateCurrentGroup(const std::string line)
{
    std::string groupName = line.substr(1, line.length() - 2);
    
    assert(m_rootGroup);
    if (m_rootGroup->name() == groupName) {
        m_currentGroup = m_rootGroup;
        return true;
    }
    
    if (m_rootGroup->groupExists(groupName)) {
        m_currentGroup = m_rootGroup->group(groupName);
        return true;
    }
    
    m_currentGroup = nullptr;
    std::cerr << "Group with name \"" << groupName << "\" does not exist" << std::endl;
    return false;
}

bool PropertyDeserializer::setPropertyValue(const std::string line)
{
    if (!m_currentGroup) {
        std::cerr << "Could not parse line\"" << line << "\"";
        std::cerr << "because no existing group was declared" << std::endl;
        return false;
    }

    std::smatch match;
    std::regex_search(line, match, std::regex("="));
    const std::string & path = match.prefix();
    m_currentValue = match.suffix();
    
    AbstractProperty * property = m_currentGroup->property(path);
    
    if (!property) {
        std::cerr << "Property path \"" << path << "\" ";
        std::cerr << "is invalid" << std::endl;
        return false;
    }

    property->accept(*this);
    return true;
}
    
void PropertyDeserializer::deserializeVectorValues(const std::string & valueRegexString,
    int size, const std::function<void(const std::string &)> & functor)
{
    std::stringstream vectorRegexStream;
    
    vectorRegexStream << "\\s*\\(";
    for (int i = 0; i < size - 1; i++) {
        vectorRegexStream << valueRegexString << ",";
    }
    vectorRegexStream << valueRegexString << "\\)\\s*";
    
    std::string string(vectorRegexStream.str());
    if (!std::regex_match(m_currentValue, std::regex(vectorRegexStream.str()))) {
        std::cerr << "Vector values does not match format:";
        std::cerr << "\"" << valueRegexString << "\"" << std::endl;
        return;
    }
    
    std::smatch match;
    std::regex_search(m_currentValue, match, std::regex(vectorRegexStream.str()));
    for (int i = 1; i < match.size(); ++i) {
        functor(match[i].str());
    }
}


void PropertyDeserializer::visit(Property<bool> & property)
{
    if (std::regex_match(m_currentValue, std::regex("\\s*true\\s*"))) {
        property.setValue(true);
        return;
    }
    
    if (std::regex_match(m_currentValue, std::regex("\\s*false\\s*"))) {
        property.setValue(false);
    }
}

void PropertyDeserializer::visit(Property<int> & property)
{
    property.setValue(this->convertString<int>(m_currentValue));
}

void PropertyDeserializer::visit(Property<unsigned int> & property)
{
    property.setValue(this->convertString<unsigned int>(m_currentValue));
}

void PropertyDeserializer::visit(Property<long> & property)
{
    property.setValue(this->convertString<long>(m_currentValue));
}

void PropertyDeserializer::visit(Property<unsigned long> & property)
{
    property.setValue(this->convertString<unsigned long>(m_currentValue));
}

void PropertyDeserializer::visit(Property<char> & property)
{
    property.setValue(this->convertString<char>(m_currentValue));
}

void PropertyDeserializer::visit(Property<unsigned char> & property)
{
    property.setValue(this->convertString<unsigned char>(m_currentValue));
}

void PropertyDeserializer::visit(Property<float> & property)
{
    property.setValue(this->convertString<float>(m_currentValue));
}

void PropertyDeserializer::visit(Property<double> & property)
{
    property.setValue(this->convertString<double>(m_currentValue));
}

void PropertyDeserializer::visit(Property<std::string> & property)
{
    property.setValue(m_currentValue);
}

void PropertyDeserializer::visit(Property<Color> & property)
{
    std::vector<int> color;
    this->deserializeVectorValues("([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])", 4,
                                  [this, &color](const std::string & string) {
                                      color.push_back(this->convertString<int>(string));
                                  });
    property.setValue(Color(color[0], color[1], color[2], color[3]));
}

void PropertyDeserializer::visit(Property<FilePath> & property)
{
    property.setValue(m_currentValue);
}

void PropertyDeserializer::visit(Property<std::vector<bool>> & property)
{
    std::vector<bool> vector;
    this->deserializeVectorValues("(true|false)", property.fixedSize(),
                                  [this, &vector](const std::string & string) {
                                      vector.push_back(string == "true" ? true : false);
                                  });
    property.setValue(vector);
}

void PropertyDeserializer::visit(Property<std::vector<int>> & property)
{
    std::vector<int> vector;
    this->deserializeVectorValues("(\\d+\\.?\\d*)", property.fixedSize(),
                                  [this, &vector](const std::string & string) {
                                      vector.push_back(this->convertString<int>(string));
                                  });
    property.setValue(vector);
}

void PropertyDeserializer::visit(Property<std::vector<float>> & property)
{
    std::vector<float> vector;
    this->deserializeVectorValues("(\\d+\\.?\\d*)", property.fixedSize(),
                                  [this, &vector](const std::string & string) {
                                      vector.push_back(this->convertString<float>(string));
                                  });
    property.setValue(vector);
}

void PropertyDeserializer::visit(Property<std::vector<double>> & property)
{
    std::vector<double> vector;
    this->deserializeVectorValues("(\\d+\\.?\\d*)", property.fixedSize(),
                                  [this, &vector](const std::string & string) {
                                      vector.push_back(this->convertString<double>(string));
                                  });
    property.setValue(vector);
}

void PropertyDeserializer::visit(PropertyGroup & property)
{
    std::cerr << "Tried to assign value to group with name: ";
    std::cerr << property.name() << std::endl;
}

} // namespace