#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <reflectionzeug/AbstractSerializer.h>

#include <vector>

#include <reflectionzeug/Variant.h>

namespace reflectionzeug
{
    
/**
 * \brief Saves values of a property hierachy in a JSON file.
 * \see JsonToVariantDeserializer
 */
    
class REFLECTIONZEUG_API JsonFromVariantSerializer : public AbstractSerializer
{
public:
    JsonFromVariantSerializer();
    virtual ~JsonFromVariantSerializer();

    virtual void writeToStream(Variant & variant, std::ostream & outStream) override;
    virtual void writeToFile(Variant & variant, const std::string & filePath) override;
    virtual std::string writeToString(Variant & variant) override;
    
protected:
    void serialize(Variant & variant, std::ostream & stream);
    void serializeVariant(Variant & variant, std::ostream & stream);
    void serializeMap(const VariantMap * map, std::ostream & stream);
    void serializeArray(const VariantArray * array, std::ostream & stream);
    void serializeValue(Variant & value, std::ostream & stream);
    void writeJsonString(Variant & value, std::ostream & stream);

    std::string indent(unsigned int nestingLevel);
    void endLine(std::ostream & stream);

protected:
    unsigned int m_nestingLevel;
    std::vector<unsigned int> m_elementCount;

};
    
} // namespace reflectionzeug
