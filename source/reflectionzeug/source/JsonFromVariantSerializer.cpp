#include <reflectionzeug/JsonFromVariantSerializer.h>

#include <memory>
#include <ostream>
#include <fstream>
#include <sstream>

#include <loggingzeug/logging.h>


using namespace loggingzeug;

namespace reflectionzeug
{

void JsonFromVariantSerializer::writeToStream(const Variant & variant, std::ostream & outStream)
{
    serialize(variant, outStream);
}

void JsonFromVariantSerializer::writeToFile(const Variant & variant, const std::string & filePath)
{
    std::ofstream fileStream {filePath};
    if (fileStream.is_open())
    {
        serialize(variant, fileStream);
    }
    else
    {
        critical() << "Could not open stream. Aborted writing to file: \"" << filePath << "\".";
    }
}

std::string JsonFromVariantSerializer::writeToString(const Variant & variant)
{
    std::ostringstream stringStream {};
    serialize(variant, stringStream);
    return stringStream.str();
}

void JsonFromVariantSerializer::serialize(const Variant & variant, std::ostream & stream)
{
    m_nestingLevel = 0;
    m_elementCount.push_back(1);

    serializeVariant(variant, stream);

    m_elementCount.clear();
}

void JsonFromVariantSerializer::serializeVariant(const Variant & variant, std::ostream & stream)
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

void JsonFromVariantSerializer::serializeMap(const VariantMap * map, std::ostream & stream)
{
    stream << "{" << std::endl;

    m_nestingLevel++;
    m_elementCount.push_back(map->size());
    for (const auto & stringVariantPair : *map)
    {
        stream << indent(m_nestingLevel) << "\"" << stringVariantPair.first << "\": ";
        serializeVariant(stringVariantPair.second, stream);
    }
    m_elementCount.pop_back();
    m_nestingLevel--;

    stream << indent(m_nestingLevel) << "}";
    endLine(stream);
}

void JsonFromVariantSerializer::serializeArray(const VariantArray * array, std::ostream & stream)
{
    stream << "[" << std::endl;

    m_nestingLevel++;
    m_elementCount.push_back(array->size());
    for (const auto & variant : *array)
    {
        stream << indent(m_nestingLevel);
        serializeVariant(variant, stream);
    }
    m_elementCount.pop_back();
    m_nestingLevel--;

    stream << indent(m_nestingLevel) << "]";
    endLine(stream);
}
    
void JsonFromVariantSerializer::serializeValue(const Variant & value, std::ostream & stream)
{
    writeJsonString(value, stream);
    endLine(stream);
}

void JsonFromVariantSerializer::writeJsonString(const Variant & value, std::ostream & stream)
{
    if (value.isNull())
    {
        stream << "null";
    }
    else if (value.hasType<bool>())
    {
        assert(value.canConvert<bool>());
        stream << (value.value<bool>() ? "true" : "false");
    }
    else if (value.hasType<float>() || value.hasType<double>())
    {
        assert(value.canConvert<double>());
        stream << value.value<double>();
    }
    else if (value.hasType<char>() || value.hasType<unsigned char>() ||
             value.hasType<int>() || value.hasType<unsigned int>() ||
             value.hasType<long>() || value.hasType<unsigned long>() ||
             value.hasType<long long>() || value.hasType<unsigned long long>())
    {
        assert(value.canConvert<long long>());
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

std::string JsonFromVariantSerializer::indent(unsigned int nestingLevel)
{
    std::string str;
    for (auto i = 0u; i < nestingLevel; ++i)
    {
        str += "    ";
    }
    return str;
}

void JsonFromVariantSerializer::endLine(std::ostream & stream)
{
    m_elementCount[m_nestingLevel]--;
    if (m_elementCount.at(m_nestingLevel) > 0)
    {
        stream << ",";
    }
    stream << std::endl;
}

} // namespace reflectionzeug
