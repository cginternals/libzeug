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
 * \see AbstractDeserializer
 */
    
class REFLECTIONZEUG_API AbstractSerializer
{
public:
    AbstractSerializer();
    virtual ~AbstractSerializer();

    virtual void writeToStream(Variant & variant, std::ostream & outStream) { }
    virtual void writeToFile(Variant & variant, const std::string & filePath) { }
    virtual std::string writeToString(Variant & variant) { return ""; }

    // deprecated
    virtual bool serialize(PropertyGroup & group, const std::string & filePath) { return false; }


};
    
} // namespace reflectionzeug
