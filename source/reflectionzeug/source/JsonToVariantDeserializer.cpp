#include <reflectionzeug/JsonToVariantDeserializer.h>

#include <iostream>
#include <fstream>
#include <memory>

#include <loggingzeug/logging.h>

#include <reflectionzeug/SetValuePropertyVisitor.h>
#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/regex_namespace.h>
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
        m_matches.clear();
        if (isMapDeclaration(line))
        {
            successFlag = insert(Variant::map()) && successFlag;
        }
        else if (isMapEnd(line))
        {
            endMap();
        }
        else if (isArrayDeclaration(line))
        {
            successFlag = insert(Variant::array()) && successFlag;
        }
        else if (isArrayEnd(line))
        {
            endArray();
        }
        else if (isKeyValueDeclaration(line))
        {
            successFlag = insert(constructVariant(m_matches.at(2))) && successFlag;
        }
        else if (isValueDeclaration(line))
        {
            successFlag = insert(constructVariant(m_matches.at(1))) && successFlag;
        }
    }

    return m_rootVariant;
}

bool JsonToVariantDeserializer::match(const std::string & regexString, const std::string & line)
{
    regex_namespace::regex regExpr(regexString);
    auto matches = regex_namespace::smatch();
    bool foundMatch = regex_namespace::regex_match(line, matches, regExpr);

    for (auto match : matches)
    {
        if (match.str().compare("") != 0)
            m_matches.push_back(match.str());
    }
    return foundMatch;
}

bool JsonToVariantDeserializer::isMapDeclaration(const std::string & line)
{
    // match '"GROUPNAME": {' and '{'
    // captures GROUPNAME
    static const std::string mapRegex(
            "^\\s*(?:\"(" + AbstractProperty::s_nameRegexString + ")\": )?\\{$");
    return match(mapRegex, line);
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
    static const std::string arrayRegex(
            "^\\s*(?:\"(" + AbstractProperty::s_nameRegexString + ")\": )?\\[$");
    return match(arrayRegex, line);
}

bool JsonToVariantDeserializer::isArrayEnd(const std::string &line)
{
    // match solitary ']' and '],'
    static const regex_namespace::regex arrayRegex("^\\s*\\],?$");
    return regex_namespace::regex_match(line, arrayRegex);
}

bool JsonToVariantDeserializer::isKeyValueDeclaration(const std::string & line)
{
    // match '"NAME": VALUE' pair with VALUE being either string, number or boolean
    // captures NAME and VALUE
    static const std::string keyValueRegex(
            "^\\s*\"(" + AbstractProperty::s_nameRegexString + ")\": (\".*\"|\\d+(?:\\.?\\d+)?|(?:true|false|null)),?$");
    return match(keyValueRegex, line);
}

bool JsonToVariantDeserializer::isValueDeclaration(const std::string & line)
{
    // match 'VALUE' with VALUE being either string, number or boolean
    // captures VALUE
    static const std::string valueRegex(
            "^\\s*(\".*\"|\\d+(?:\\.?\\d+)?|(?:true|false|null)),?$");
    return match(valueRegex, line);
}

bool JsonToVariantDeserializer::isKeyValue(Variant variant) const
{
    if (variant.isArray() || variant.isMap())
    {
        return m_matches.size() == 2;
    }
    else
    {
        return m_matches.size() == 3;
    }
}

bool JsonToVariantDeserializer::isValue(Variant variant) const
{
    if (variant.isArray() || variant.isMap())
    {
        return m_matches.size() == 1;
    }
    else
    {
        return m_matches.size() == 2;
    }
}

bool JsonToVariantDeserializer::insert(Variant variant)
{
    if (m_variantGroupList.empty())
    {
        m_rootVariant = variant;
        updateGroupList(&m_rootVariant);
    }
    else if (m_variantGroupList.back()->isMap())
    {
        if (isKeyValue(variant))
        {
            auto variantMap = m_variantGroupList.back()->toMap();
            variantMap->insert(std::pair<std::string, Variant>(m_matches.at(1), variant));
            updateGroupList(&(variantMap->at(m_matches.at(1))));
        }
    }
    else if (m_variantGroupList.back()->isArray())
    {
        if (isValue(variant))
        {
            auto variantArray = m_variantGroupList.back()->toArray();
            variantArray->push_back(variant);
            updateGroupList(&(variantArray->back()));
        }
    }
    else
    {
        return false;
    }
    return true;
}

void JsonToVariantDeserializer::updateGroupList(Variant * variant)
{
    if (variant->isArray() || variant->isMap())
    {
        m_variantGroupList.push_back(variant);
    }
}

void JsonToVariantDeserializer::endMap()
{
    m_variantGroupList.pop_back();
}

void JsonToVariantDeserializer::endArray()
{
    m_variantGroupList.pop_back();
}

Variant JsonToVariantDeserializer::constructVariant(const std::string & value) const
{
    debug() << "constructing variant from value " << value;
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
