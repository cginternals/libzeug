#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <string>
#include <ostream>

namespace reflectionzeug
{

class PropertyGroup;
class Variant;
    
/**
 * \brief Interface for Serialization Classes.
 * \see AbstractPropertyDeserializer
 */
    
class REFLECTIONZEUG_API AbstractSerializer
{
public:
    AbstractSerializer();
    virtual ~AbstractSerializer();

    virtual bool serialize(PropertyGroup & group, const std::string & filePath) { return false; }
    virtual void serialize(Variant & variant, std::ostream * outStream) { }
    virtual std::string serialize(Variant & variant) { return ""; }

};
    
} // namespace reflectionzeug
