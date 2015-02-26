#include <reflectionzeug/JsonVariantSerializer.h>

#include <memory>
#include <ostream>
#include <fstream>
#include <sstream>

#include <loggingzeug/logging.h>


using namespace loggingzeug;

namespace reflectionzeug
{
    
JsonVariantSerializer::JsonVariantSerializer()
    : m_nestingLevel(0)
{
}

JsonVariantSerializer::~JsonVariantSerializer()
{
}

void JsonVariantSerializer::writeToStream(Variant & variant, std::ostream & outStream)
{
    serialize(variant, outStream);
}

void JsonVariantSerializer::writeToFile(Variant & variant, const std::string & filePath)
{
    auto fileStream = std::unique_ptr<std::ofstream>(new std::ofstream(filePath));
    if (fileStream->is_open())
    {
        serialize(variant, *fileStream);
    }
    else
    {
        critical() << "Could not open stream. Aborted writing to file: \"" << filePath << "\".";
    }
}

std::string JsonVariantSerializer::writeToString(Variant & variant)
{
    auto stringStream = std::unique_ptr<std::ostringstream>(new std::ostringstream());
    serialize(variant, *stringStream);
    return stringStream->str();
}

void JsonVariantSerializer::serialize(Variant & variant, std::ostream & stream)
{
    m_nestingLevel = 0;
    m_elementCount.push_back(1);

    serializeVariant(variant, stream);

    m_elementCount.clear();
}

void JsonVariantSerializer::serializeVariant(Variant & variant, std::ostream & stream)
{
    if (variant.isMap())
    {
        serializeMap(variant.toMap(), stream);
    }
    else if (variant.isArray())
    {
        serializeArray(variant.toArray(), stream);
    }
    else
    {
        serializeValue(variant, stream);
    }
}

void JsonVariantSerializer::serializeMap(const VariantMap * map, std::ostream & stream)
{
    stream << "{" << std::endl;

    m_nestingLevel++;
    m_elementCount.push_back(map->size());
    for (auto stringVariantPair : *map)
    {
        stream << indent(m_nestingLevel) << "\"" << stringVariantPair.first << "\": ";
        serializeVariant(stringVariantPair.second, stream);
    }
    m_elementCount.pop_back();
    m_nestingLevel--;

    stream << indent(m_nestingLevel) << "}";
    endLine(stream);
}

void JsonVariantSerializer::serializeArray(const VariantArray * array, std::ostream & stream)
{
    stream << "[" << std::endl;

    m_nestingLevel++;
    m_elementCount.push_back(array->size());
    for (auto variant : *array)
    {
        serializeVariant(variant, stream);
    }
    m_elementCount.pop_back();
    m_nestingLevel--;

    stream << indent(m_nestingLevel) << "]";
    endLine(stream);
}
    
void JsonVariantSerializer::serializeValue(Variant & value, std::ostream & stream)
{
    writeJsonString(value, stream);
    endLine(stream);
}

void JsonVariantSerializer::writeJsonString(Variant & value, std::ostream & stream)
{
    if (value.isNull())
    {
        stream << "null";
    }
    else if (value.hasType<bool>() && value.canConvert<bool>())
    {
        stream << (value.value<bool>() ? "true" : "false");
    }
    else if ((value.hasType<float>() || value.hasType<double>()) &&
             value.canConvert<double>())
    {
        stream << value.value<double>();
    }
    else if ((value.hasType<char>() || value.hasType<unsigned char>() ||
             value.hasType<int>() || value.hasType<unsigned int>() ||
             value.hasType<long>() || value.hasType<unsigned long>() ||
             value.hasType<long long>() || value.hasType<unsigned long long>()) &&
             value.canConvert<long long>())
    {
        stream << value.value<long long>();
    }
    else if (value.canConvert<std::string>())
    {
        stream << "\"" << value.value<std::string>() << "\"";
    }
    else
    {
        critical() << "Could not serialize value, please register appropriate converter." << std::endl;
        stream << "null";
    }
}

std::string JsonVariantSerializer::indent(unsigned int nestingLevel)
{
    std::string str;
    for (unsigned int i = 0; i < nestingLevel; i++)
    {
        str += "    ";
    }
    return str;
}

void JsonVariantSerializer::endLine(std::ostream & stream)
{
    m_elementCount[m_nestingLevel]--;
    if (m_elementCount.at(m_nestingLevel) > 0)
    {
        stream << ",";
    }
    stream << std::endl;
}

} // namespace reflectionzeug
