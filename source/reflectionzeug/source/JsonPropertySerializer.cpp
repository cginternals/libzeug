#include <reflectionzeug/JsonPropertySerializer.h>

#include <iostream>

#include <loggingzeug/logging.h>

#include <reflectionzeug/util.h>

using namespace loggingzeug;

namespace reflectionzeug
{
    
JsonPropertySerializer::JsonPropertySerializer(std::ostream & stream)
    : m_ostream(stream)
    , m_nestingLevel(0)
{
}

JsonPropertySerializer::~JsonPropertySerializer()
{
}

bool JsonPropertySerializer::serialize(Variant & variant)
{
    m_nestingLevel = 0;
    m_elementCount.push_back(1);

    serializeVariant(variant);

    m_elementCount.clear();
    return true;
}

void JsonPropertySerializer::serializeVariant(Variant & variant)
{
    if (variant.isMap())
    {
        serializeMap(variant.toMap());
    }
    else if (variant.isArray())
    {
        serializeArray(variant.toArray());
    }
    else
    {
        serializeValue(variant);
    }
}

void JsonPropertySerializer::serializeMap(const VariantMap * map)
{
    m_ostream << "{" << std::endl;

    m_nestingLevel++;
    m_elementCount.push_back(map->size());
    for (auto stringVariantPair : *map)
    {
        m_ostream << indent(m_nestingLevel) << "\"" << stringVariantPair.first << "\": ";
        serializeVariant(stringVariantPair.second);
    }
    m_elementCount.pop_back();
    m_nestingLevel--;

    m_ostream << indent(m_nestingLevel) << "}";
    endLine();
}

void JsonPropertySerializer::serializeArray(const VariantArray * array)
{
    m_ostream << "[" << std::endl;

    m_nestingLevel++;
    m_elementCount.push_back(array->size());
    for (auto variant : *array)
    {
        serializeVariant(variant);
    }
    m_elementCount.pop_back();
    m_nestingLevel--;

    m_ostream << indent(m_nestingLevel) << "]";
    endLine();
}
    
void JsonPropertySerializer::serializeValue(Variant & value)
{
    writeJsonString(value);
    endLine();
}

void JsonPropertySerializer::writeJsonString(Variant & value)
{
    if (value.isNull())
    {
        m_ostream << "null";
    }
    else if (value.hasType<bool>() && value.canConvert<bool>())
    {
        m_ostream << (value.value<bool>() ? "true" : "false");
    }
    else if ((value.hasType<float>() || value.hasType<double>()) &&
             value.canConvert<double>())
    {
        m_ostream << value.value<double>();
    }
    else if ((value.hasType<char>() || value.hasType<unsigned char>() ||
             value.hasType<int>() || value.hasType<unsigned int>() ||
             value.hasType<long>() || value.hasType<unsigned long>() ||
             value.hasType<long long>() || value.hasType<unsigned long long>()) &&
             value.canConvert<long long>())
    {
        m_ostream << value.value<long long>();
    }
    else if (value.canConvert<std::string>())
    {
        m_ostream << "\"" << value.value<std::string>() << "\"";
    }
    else
    {
        critical() << "Could not serialize value, please register appropriate converter." << std::endl;
        m_ostream << "null";
    }
}

std::string JsonPropertySerializer::indent(unsigned int nestingLevel)
{
    std::string str;
    for (unsigned int i = 0; i < nestingLevel; i++)
    {
        str += "    ";
    }
    return str;
}

void JsonPropertySerializer::endLine()
{
    m_elementCount[m_nestingLevel]--;
    if (m_elementCount.at(m_nestingLevel) > 0)
    {
        m_ostream << ",";
    }
    m_ostream << std::endl;
}

} // namespace reflectionzeug
