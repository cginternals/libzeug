

#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif

#include <iostream>
#include <fstream>

#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>

#include <reflectionzeug/PropertyDeserializer.h>

namespace reflectionzeug
{

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
    static const regex_namespace::regex groupRegex("\\[" + AbstractProperty::s_nameRegexString + "\\]");

    return regex_namespace::regex_match(line, groupRegex);
}

bool PropertyDeserializer::isPropertyDeclaration(const std::string line)
{
    static const regex_namespace::regex propertyRegex(AbstractProperty::s_nameRegexString +
                                          "(\\/" +
                                          AbstractProperty::s_nameRegexString +
                                          ")*=.+");

    return regex_namespace::regex_match(line, propertyRegex);
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

    regex_namespace::smatch match;
    regex_namespace::regex_search(line, match, regex_namespace::regex("="));
    const std::string & path = match.prefix();
    m_currentValue = match.suffix();
    
    AbstractProperty * property = m_currentGroup->property(path)->asValue();
    
    if (!property) {
        std::cerr << "Property path \"" << path << "\" ";
        std::cerr << "is invalid" << std::endl;
        return false;
    }

    if (property->isGroup()) {
        std::cerr << "Tried to assign value to group with name: ";
        std::cerr << property->name() << std::endl;
        return false;
    }

    visit(*property->asValue());
    return true;
}
    
void PropertyDeserializer::deserializeVectorValues(const std::string & valueRegexString,
    int size, const std::function<void(const std::string &)> & functor)
{
    std::stringstream vectorRegexStream;
    
    vectorRegexStream << "\\s*\\(";
    for (int i = 0; i < size - 1; i++) {
        vectorRegexStream << valueRegexString << ",\\s?";
    }
    vectorRegexStream << valueRegexString << "\\)\\s*";
    
    std::string string(vectorRegexStream.str());
    if (!regex_namespace::regex_match(m_currentValue, regex_namespace::regex(vectorRegexStream.str()))) {
        std::cerr << "Vector values does not match format:";
        std::cerr << "\"" << valueRegexString << "\"" << std::endl;
        return;
    }
    
    regex_namespace::smatch match;
    regex_namespace::regex_search(m_currentValue, match, regex_namespace::regex(vectorRegexStream.str()));
    for (unsigned int i = 1; i < match.size(); ++i) {
        functor(match[i].str());
    }
}

void PropertyDeserializer::deserializeSetValues(const std::string & valueRegexString,
    const std::function<void(const std::string &)> & functor)
{
    std::stringstream vectorRegexStream;
    vectorRegexStream << "\\s*\\(";
    vectorRegexStream << "("+valueRegexString+"|"+valueRegexString+"\\s*(,\\s*"+valueRegexString+")";
    vectorRegexStream << "\\)\\s*";
    
    std::string string(vectorRegexStream.str());
    if (!regex_namespace::regex_match(m_currentValue, regex_namespace::regex(vectorRegexStream.str()))) {
        std::cerr << "Vector values does not match format:";
        std::cerr << "\"" << valueRegexString << "\"" << std::endl;
        return;
    }
    
    regex_namespace::smatch match;
    regex_namespace::regex_search(m_currentValue, match, regex_namespace::regex(vectorRegexStream.str()));
    for (unsigned int i = 1; i < match.size(); ++i) {
        functor(match[i].str());
    }
}


void PropertyDeserializer::visitBool(Property<bool> & property)
{
    if (regex_namespace::regex_match(m_currentValue, regex_namespace::regex("\\s*true\\s*"))) {
        property.setValue(true);
        return;
    }
    
    if (regex_namespace::regex_match(m_currentValue, regex_namespace::regex("\\s*false\\s*"))) {
        property.setValue(false);
    }
}

void PropertyDeserializer::visitInt(Property<int> & property)
{
    property.setValue(this->convertString<int>(m_currentValue));
}

void PropertyDeserializer::visitDouble(Property<double> & property)
{
    property.setValue(this->convertString<double>(m_currentValue));
}

void PropertyDeserializer::visitString(Property<std::string> & property)
{
    property.setValue(m_currentValue);
}

void PropertyDeserializer::visitColor(Property<Color> & property)
{
    regex_namespace::regex colorHexRegex("#[0-9A-F]{8}");
    if (!regex_namespace::regex_match(m_currentValue, colorHexRegex)) {
        std::cerr << "Color value does not match format: " << property.name() << std::endl;
        return;
    }
    
    std::stringstream stream(m_currentValue.substr(1, m_currentValue.length()));
    unsigned int colorHex;
    stream >> std::hex >> std::uppercase;
    stream >> colorHex;
    property.setValue(Color(colorHex));
}

void PropertyDeserializer::visitFilePath(Property<FilePath> & property)
{
    property.setValue(m_currentValue);
}

void PropertyDeserializer::visitBoolVector(Property<std::vector<bool>> & property)
{
    std::vector<bool> vector;
    this->deserializeVectorValues("(true|false)", property.fixedSize(),
                                  [this, &vector](const std::string & string) {
                                      vector.push_back(string == "true" ? true : false);
                                  });
    property.setValue(vector);
}

void PropertyDeserializer::visitIntVector(Property<std::vector<int>> & property)
{
    std::vector<int> vector;
    this->deserializeVectorValues("(-?\\d+)", property.fixedSize(),
                                  [this, &vector](const std::string & string) {
                                      vector.push_back(this->convertString<int>(string));
                                  });
    property.setValue(vector);
}

void PropertyDeserializer::visitDoubleVector(Property<std::vector<double>> & property)
{
    std::vector<double> vector;
    this->deserializeVectorValues("(-?\\d+\\.?\\d*)", property.fixedSize(),
                                  [this, &vector](const std::string & string) {
                                      vector.push_back(this->convertString<double>(string));
                                  });
    property.setValue(vector);
}

void PropertyDeserializer::visitIntSet(Property<std::set<int>> & property)
{
    std::set<int> set;
    this->deserializeSetValues("(-?\\d+)", [this, &set](const std::string & string) {
	set.insert(this->convertString<int>(string));
    });
    property.setValue(set);
}

} // namespace reflectionzeug
