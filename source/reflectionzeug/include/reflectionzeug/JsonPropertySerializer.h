#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <reflectionzeug/AbstractPropertySerializer.h>

#include <deque>
#include <fstream>
#include <functional>

namespace reflectionzeug
{

class AbstractValueProperty;
class PropertyGroup;
    
/**
 * \brief Saves values of a property hierachy in a JSON file.
 * \see JsonPropertyDeserializer
 */
    
class REFLECTIONZEUG_API JsonPropertySerializer : public AbstractPropertySerializer
{
public:
    JsonPropertySerializer();
    virtual ~JsonPropertySerializer();

    virtual bool serialize(PropertyGroup & group, const std::string & filePath) override;
    
protected:
    void serializeValue(AbstractValueProperty & property);
    std::string indent(unsigned int nestingLevel);

protected:
    std::fstream m_fstream;
    unsigned int m_nestingLevel;
    std::function<void(PropertyGroup &)> m_serialize;

};
    
} // namespace reflectionzeug
