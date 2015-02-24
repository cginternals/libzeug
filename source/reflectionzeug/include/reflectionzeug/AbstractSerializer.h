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
    virtual bool serialize(Variant & variant) { return false; }

};
    
} // namespace reflectionzeug
