#include <reflectionzeug/JsonPropertySerializer.h>

#include <iostream>

#include <loggingzeug/logging.h>

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/JsonSerializationVisitor.h>
#include <reflectionzeug/ValueProperty.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/util.h>

using namespace loggingzeug;

namespace reflectionzeug
{
    
JsonPropertySerializer::JsonPropertySerializer()
    : m_nestingLevel(0)
{
    m_serialize =
        [this](PropertyGroup & group)
        {
            m_elementCount[m_nestingLevel]--;

            m_fstream << indent(m_nestingLevel);
            if (!group.name().empty())
            {
                m_fstream << "\"" << group.name() << "\": ";
            }
            m_fstream << "{" << std::endl;

            m_nestingLevel++;
            m_elementCount.push_back(group.asCollection()->count());

            group.forEachValue(
                [this](AbstractValueProperty & property)
                {
                    m_elementCount[m_nestingLevel]--;
                    serializeValue(property);
                }
            );

            group.forEachGroup(m_serialize);
            m_nestingLevel--;
            m_fstream << indent(m_nestingLevel) << "}";
            if (m_elementCount.at(m_nestingLevel) > 0)
            {
                m_fstream << ",";
            }
            m_fstream << std::endl;
            m_elementCount.pop_back();
        };
}

JsonPropertySerializer::~JsonPropertySerializer()
{
}
    
bool JsonPropertySerializer::serialize(PropertyGroup & group, const std::string & filePath)
{
    m_fstream.open(filePath, std::ios_base::out);
    
    if (!m_fstream.is_open()) {
        critical() << "Could not write to file \"" << filePath << "\"" << std::endl;
        return false;
    }
    m_nestingLevel = 0;
    m_elementCount.push_back(1);

    m_serialize(group);

    m_elementCount.clear();
    m_fstream.close();
    return true;
}
    
void JsonPropertySerializer::serializeValue(AbstractValueProperty & property)
{
    JsonSerializationVisitor visitor;
    property.accept(&visitor);
    std::string valueString = visitor.propertyValue();
    m_fstream << indent(m_nestingLevel) << "\"" << property.name() << "\": " << valueString;
    if (m_elementCount.at(m_nestingLevel) > 0)
    {
        m_fstream << ",";
    }
    m_fstream << std::endl;
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

} // namespace reflectionzeug
