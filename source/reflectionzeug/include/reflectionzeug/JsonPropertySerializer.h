#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <reflectionzeug/AbstractSerializer.h>
#include <reflectionzeug/Variant.h>

#include <vector>

namespace reflectionzeug
{
    
/**
 * \brief Saves values of a property hierachy in a JSON file.
 * \see JsonPropertyDeserializer
 */
    
class REFLECTIONZEUG_API JsonPropertySerializer : public AbstractSerializer
{
public:
    JsonPropertySerializer(std::ostream & stream);
    virtual ~JsonPropertySerializer();

    virtual bool serialize(Variant & variant) override;
    
protected:
    void serializeVariant(Variant & variant);
    void serializeMap(const VariantMap * map);
    void serializeArray(const VariantArray * array);
    void serializeValue(Variant & value);
    void writeJsonString(Variant & value);
    std::string indent(unsigned int nestingLevel);
    void endLine();

protected:
    std::ostream & m_ostream;
    unsigned int m_nestingLevel;
    std::vector<unsigned int> m_elementCount;

};
    
} // namespace reflectionzeug
