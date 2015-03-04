#include <reflectionzeug/JsonToVariantDeserializer.h>

#include <iostream>
#include <fstream>
#include <memory>

#include <loggingzeug/logging.h>

#include <reflectionzeug/SetValuePropertyVisitor.h>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/util.h>

using namespace loggingzeug;

namespace reflectionzeug
{

JsonToVariantDeserializer::JsonToVariantDeserializer()
{
}

JsonToVariantDeserializer::~JsonToVariantDeserializer()
{
}

Variant JsonToVariantDeserializer::fromStream(std::istream & inStream)
{
    bool successFlag = true;
    return fromStream(inStream, successFlag);
}

Variant JsonToVariantDeserializer::fromStream(std::istream & inStream, bool & successFlag)
{
    return deserialize(inStream, successFlag);
}

Variant JsonToVariantDeserializer::fromFile(const std::string & filePath)
{
    bool successFlag = true;
    return fromFile(filePath, successFlag);
}

Variant JsonToVariantDeserializer::fromFile(const std::string & filePath, bool & successFlag)
{
    auto stream = std::unique_ptr<std::ifstream>(new std::ifstream(filePath));
    if (stream->is_open())
    {
        return deserialize(*stream, successFlag);
    }
    else
    {
        critical() << "Could not open stream from file: \"" << filePath << "\"";
        return Variant();
    }
}

Variant JsonToVariantDeserializer::fromString(const std::string & str)
{
    bool successFlag = true;
    return fromString(str, successFlag);
}

Variant JsonToVariantDeserializer::fromString(const std::string & str, bool & successFlag)
{
    auto stream = std::unique_ptr<std::istringstream>(new std::istringstream(str));
    return deserialize(*stream, successFlag);
}

Variant JsonToVariantDeserializer::deserialize(std::istream & inStream, bool & successFlag)
{
    successFlag = true;
    m_variantGroupList.clear();

    for (std::string line; std::getline(inStream, line);)
    {
        debug() << line;
        if (isMapDeclaration(line))
        {
            successFlag = insert(Variant::map()) && successFlag;
        }
        else if (isMapEnd(line))
            endMap();
        else if (isArrayDeclaration(line))
        {
            successFlag = insert(Variant::array()) && successFlag;
        }
        else if (isArrayEnd(line))
            endArray();
        else if (isValueDeclaration(line))
        {
            successFlag = insert(constructVariant(m_matches[2])) && successFlag;
        }
    }

    return m_rootVariant;
}

bool JsonToVariantDeserializer::isMapDeclaration(const std::string & line)
{
    // match '"GROUPNAME": {' and '{'
    // captures GROUPNAME
    static const regex_namespace::regex mapRegex(
            "^\\s*(?:\"(" + AbstractProperty::s_nameRegexString + ")\": )?\\{$");
    m_matches = regex_namespace::smatch();
    return regex_namespace::regex_match(line, m_matches, mapRegex);
}

bool JsonToVariantDeserializer::isMapEnd(const std::string &line)
{
    // match solitary '}' and '},'
    static const regex_namespace::regex mapRegex("^\\s*\\},?$");

    return regex_namespace::regex_match(line, mapRegex);
}

bool JsonToVariantDeserializer::isArrayDeclaration(const std::string & line)
{
    // match '"GROUPNAME": [' and '['
    // captures GROUPNAME
    static const regex_namespace::regex arrayRegex(
            "^\\s*(?:\"(" + AbstractProperty::s_nameRegexString + ")\": )?\\[$");
    m_matches = regex_namespace::smatch();
    return regex_namespace::regex_match(line, m_matches, arrayRegex);
}

bool JsonToVariantDeserializer::isArrayEnd(const std::string &line)
{
    // match solitary ']' and '],'
    static const regex_namespace::regex arrayRegex("^\\s*\\],?$");

    return regex_namespace::regex_match(line, arrayRegex);
}

bool JsonToVariantDeserializer::isValueDeclaration(const std::string & line)
{
    // match '"NAME": VALUE' pair with VALUE being either string, number or boolean
    // captures NAME and VALUE
    static const regex_namespace::regex valueRegex(
            "^\\s*\"(" + AbstractProperty::s_nameRegexString + ")\": (\".*\"|\\d+(?:\\.?\\d+)?|(?:true|false|null)),?$");
    m_matches = regex_namespace::smatch();
    return regex_namespace::regex_match(line, m_matches, valueRegex);
}

bool JsonToVariantDeserializer::insert(Variant variant)
{
    if (m_variantGroupList.empty())
    {
        m_rootVariant = variant;
        if (m_rootVariant.isArray() || m_rootVariant.isMap())
        {
            m_variantGroupList.push_back(&m_rootVariant);
        }
    }
    else if (m_variantGroupList.back()->isMap())
    {
        auto variantMap = m_variantGroupList.back()->toMap();
        variantMap->insert(std::pair<std::string, Variant>(m_matches[1], variant));
        if (variantMap->at(m_matches[1]).isArray() || variantMap->at(m_matches[1]).isMap())
        {
            m_variantGroupList.push_back(&(variantMap->at(m_matches[1])));
        }
    }
    else if (m_variantGroupList.back()->isArray())
    {
        auto variantArray = m_variantGroupList.back()->toArray();
        variantArray->push_back(variant);
        if (variantArray->back().isArray() || variantArray->back().isMap())
        {
            m_variantGroupList.push_back(&(variantArray->back()));
        }
    }
    else
    {
        return false;
    }
    return true;
}

void JsonToVariantDeserializer::endMap()
{
    m_variantGroupList.pop_back();
}

void JsonToVariantDeserializer::endArray()
{
    m_variantGroupList.pop_back();
}

//bool JsonToVariantDeserializer::setPropertyValue(const std::string & line)
//{
//    if (m_variantGroupList.size() == 0)
//    {
//        warning() << "Could not parse line\"" << line << "\"" << "because no existing group was declared" << std::endl;
//        return false;
//    }

//    assert(m_matches.size() == 3);
//    std::string name = m_matches[1];
//    std::string value = m_matches[2];

//    AbstractValueProperty * valueProperty = dynamic_cast<AbstractValueProperty *>(m_variantGroupList.back()->property(name));
//    if (valueProperty)
//    {
//        static SetValuePropertyVisitor visitor;
//        visitor.setVariant(constructVariant(value));
//        valueProperty->accept(&visitor);
//    }
//    else
//    {
//        warning() << "Property is not a ValueProperty, unable to assign a value" << std::endl;
//    }
//    return true;
//}

Variant JsonToVariantDeserializer::constructVariant(const std::string & value) const
{
    // subexpressions
    static const std::string r_ulonglong = "(?:0|[1-9]\\d*)";
    static const std::string r_longlong = "-?" + r_ulonglong;
    static const std::string r_double = r_longlong + "\\.\\d+";

    static const regex_namespace::regex boolRegex("^(true|false|null)$");
    static const regex_namespace::regex doubleRegex("^" + r_double + "$");
    static const regex_namespace::regex uLongLongRegex("^" + r_ulonglong + "$");
    static const regex_namespace::regex longLongRegex("^" + r_longlong + "$");
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
    else if(regex_namespace::regex_match(value, match, stringRegex))
    {
        return Variant::fromValue<std::string>(match[1]);
    }
    return Variant();
}

} // namespace reflectionzeug
