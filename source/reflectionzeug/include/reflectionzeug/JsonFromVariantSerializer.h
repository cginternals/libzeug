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

    virtual void writeToStream(const Variant & variant, std::ostream & outStream) override;
    virtual void writeToFile(const Variant & variant, const std::string & filePath) override;
    virtual std::string writeToString(const Variant & variant) override;
    
protected:
    void serialize(const Variant & variant, std::ostream & stream);
    void serializeVariant(const Variant & variant, std::ostream & stream);
    void serializeMap(const VariantMap * map, std::ostream & stream);
    void serializeArray(const VariantArray * array, std::ostream & stream);
    void serializeValue(const Variant & value, std::ostream & stream);
    void writeJsonString(const Variant & value, std::ostream & stream);

    std::string indent(unsigned int nestingLevel);
    void endLine(std::ostream & stream);

protected:
    unsigned int m_nestingLevel;
    std::vector<unsigned int> m_elementCount;

};
    
} // namespace reflectionzeug
