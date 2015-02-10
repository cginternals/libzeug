#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <string>

namespace reflectionzeug
{

class PropertyGroup;
    
/**
 * \brief Interface for Property Serialization Classes.
 * \see AbstractPropertyDeserializer
 */
    
class REFLECTIONZEUG_API AbstractPropertySerializer
{
public:
    AbstractPropertySerializer();
    virtual ~AbstractPropertySerializer();

    virtual bool serialize(PropertyGroup & group, const std::string & filePath) = 0;

};
    
} // namespace reflectionzeug
