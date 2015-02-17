#include <reflectionzeug/JsonPropertyDeserializer.h>

#include <iostream>
#include <fstream>

#include <loggingzeug/logging.h>

#include <reflectionzeug/SetValuePropertyVisitor.h>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/util.h>

using namespace loggingzeug;

namespace reflectionzeug
{

JsonPropertyDeserializer::JsonPropertyDeserializer()
:   m_rootGroup(nullptr)
{
}

JsonPropertyDeserializer::~JsonPropertyDeserializer()
{
}

bool JsonPropertyDeserializer::deserialize(PropertyGroup & group, const std::string & filePath)
{
    std::fstream fstream;
    fstream.open(filePath, std::ios_base::in);
    if (!fstream.is_open())
    {
        critical() << "Could not open file \"" << filePath << "\"" << std::endl;
        return false;
    }

    bool noErrorsOccured = true;
    m_rootGroup = &group;

    for (std::string line; std::getline(fstream, line);)
    {
        if (this->isGroupDeclaration(line))
            noErrorsOccured = this->updateCurrentGroup(line) && noErrorsOccured;
        else if (this->isGroupEnd(line))
            this->endGroup();
        else if (this->isPropertyDeclaration(line))
            noErrorsOccured = this->setPropertyValue(line) && noErrorsOccured;
    }

    fstream.close();

    return noErrorsOccured;
}

bool JsonPropertyDeserializer::isGroupDeclaration(const std::string & line)
{
    // match '"GROUPNAME": {' and '{'
    // captures GROUPNAME
    static const regex_namespace::regex groupRegex(
            "^\\s*(?:\"(" + AbstractProperty::s_nameRegexString + ")\": )?\\{$");
    m_matches = regex_namespace::smatch();
    return regex_namespace::regex_match(line, m_matches, groupRegex);
}

bool JsonPropertyDeserializer::isGroupEnd(const std::string &line)
{
    // match solitary '}' and '},'
    static const regex_namespace::regex groupRegex("^\\s*\\},?$");

    return regex_namespace::regex_match(line, groupRegex);
}

bool JsonPropertyDeserializer::isPropertyDeclaration(const std::string & line)
{
    // match '"NAME": VALUE' pair with VALUE being either string, number or boolean
    // captures NAME and VALUE
    static const regex_namespace::regex propertyRegex(
            "^\\s*\"(" + AbstractProperty::s_nameRegexString + ")\": (\".*\"|\\d+(?:\\.?\\d+)?|(?:true|false|null)),?$");
    m_matches = regex_namespace::smatch();
    return regex_namespace::regex_match(line, m_matches, propertyRegex);
}

bool JsonPropertyDeserializer::updateCurrentGroup(const std::string & line)
{
    assert(m_rootGroup);

    std::string groupName;
    if (m_rootGroup->name().compare(m_matches[1]) == 0)
    {
        m_groupStack.clear();
        m_groupStack.push_back(m_rootGroup);
        return true;
    }
    else
    {
        groupName = m_matches[1];
    }

    if (m_groupStack.back()->groupExists(groupName))
    {
        m_groupStack.push_back(m_groupStack.back()->group(groupName));
        return true;
    }

    critical() << "Group with name \"" << groupName << "\" does not exist" << std::endl;
    return false;
}

void JsonPropertyDeserializer::endGroup()
{
    m_groupStack.pop_back();
}

bool JsonPropertyDeserializer::setPropertyValue(const std::string & line)
{
    if (m_groupStack.size() == 0)
    {
        critical() << "Could not parse line\"" << line << "\"" << "because no existing group was declared" << std::endl;
        return false;
    }

    assert(m_matches.size() == 3);
    std::string name = m_matches[1];
    std::string value = m_matches[2];

    AbstractValueProperty * valueProperty = dynamic_cast<AbstractValueProperty *>(m_groupStack.back()->property(name));
    if (valueProperty)
    {
        static SetValuePropertyVisitor visitor;
        visitor.setVariant(constructVariant(value));
        valueProperty->accept(&visitor);
    }
    else
    {
        critical() << "Property is not a ValueProperty, unable to assign a value" << std::endl;
    }
    return true;
}

Variant JsonPropertyDeserializer::constructVariant(const std::string & value) const
{
    // subexpressions
    static const std::string r_ulonglong = "(?:0|[1-9]\\d*)";
    static const std::string r_longlong = "-?" + r_ulonglong;
    static const std::string r_double = r_longlong + "\\.\\d+";
    static const std::string r_number = r_longlong + "(?:\\.\\d+)?";

    static const regex_namespace::regex boolRegex("^(true|false|null)$");
    static const regex_namespace::regex doubleRegex("^" + r_double + "$");
    static const regex_namespace::regex uLongLongRegex("^" + r_ulonglong + "$");
    static const regex_namespace::regex longLongRegex("^" + r_longlong + "$");
    static const regex_namespace::regex vec3Regex("^\"\\( ?(" + r_number + "), (" + r_number + "), (" + r_number + ") ?\\)\"$");
    // matches any string '"STRING"' and captures 'STRING'
    // '"' and '\' are not allowed except '\' followed by a letter
    static const regex_namespace::regex stringRegex("^\"((?:[^\"\\\\]|(?:\\\\\\w))*)\"$");

    regex_namespace::smatch match;

    if (regex_namespace::regex_match(value, boolRegex))
    {
        // null becomes false
        return Variant::fromValue<bool>(value.compare("true") == 0 ? true : false);
    }
    else if(regex_namespace::regex_match(value, doubleRegex))
    {
        return Variant::fromValue<double>(util::fromString<double>(value));
    }
    else if(regex_namespace::regex_match(value, uLongLongRegex))
    {
        return Variant::fromValue<unsigned long long>(util::fromString<unsigned long long>(value));
    }
    else if(regex_namespace::regex_match(value, longLongRegex))
    {
        return Variant::fromValue<long long>(util::fromString<long long>(value));
    }
    else if(regex_namespace::regex_match(value, match, vec3Regex))
    {
        double x = util::fromString<double>(match[1]);
        double y = util::fromString<double>(match[2]);
        double z = util::fromString<double>(match[3]);
        return Variant::fromValue<glm::vec3>(glm::vec3(x, y, z));
    }
    else if(regex_namespace::regex_match(value, match, stringRegex))
    {
        return Variant::fromValue<std::string>(match[1]);
    }
    return Variant();
}

} // namespace reflectionzeug
