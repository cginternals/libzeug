#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <reflectionzeug/AbstractSerializer.h>
#include <reflectionzeug/Variant.h>

#include <memory>
#include <vector>

namespace reflectionzeug
{
    
/**
 * \brief Saves values of a property hierachy in a JSON file.
 * \see JsonPropertyDeserializer
 */
    
class REFLECTIONZEUG_API JsonVariantSerializer : public AbstractSerializer
{
public:
    JsonVariantSerializer();
    virtual ~JsonVariantSerializer();

    virtual void serialize(Variant & variant, std::ostream * outStream) override;
    virtual std::string serialize(Variant & variant) override;
    
protected:
    std::ostream & stream();
    void startSerializing(Variant & variant);
    void serializeVariant(Variant & variant);
    void serializeMap(const VariantMap * map);
    void serializeArray(const VariantArray * array);
    void serializeValue(Variant & value);
    void writeJsonString(Variant & value);
    std::string indent(unsigned int nestingLevel);
    void endLine();

protected:
    std::ostream * m_outStream;
    std::unique_ptr<std::ostringstream> m_stringStream;
    unsigned int m_nestingLevel;
    std::vector<unsigned int> m_elementCount;

};
    
} // namespace reflectionzeug
