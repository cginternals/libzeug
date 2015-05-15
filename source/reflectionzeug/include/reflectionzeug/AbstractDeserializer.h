#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <string>
#include <ostream>

#include <reflectionzeug/Variant.h>

namespace reflectionzeug
{

class PropertyGroup;
    
/**
 * \brief Interface for Deserialization Classes.
 * \see AbstractSerializer
 */
    
class REFLECTIONZEUG_API AbstractDeserializer
{
public:
    AbstractDeserializer() {}
    virtual ~AbstractDeserializer() {}

    virtual Variant fromStream(std::istream & inStream) { return Variant(); }
    virtual Variant fromStream(std::istream & inStream, bool & successFlag) { return Variant(); }
    virtual Variant fromFile(const std::string & filePath) { return Variant(); }
    virtual Variant fromFile(const std::string & filePath, bool & successFlag) { return Variant(); }
    virtual Variant fromString(const std::string & str) { return Variant(); }
    virtual Variant fromString(const std::string & str, bool & successFlag) { return Variant(); }

    // deprecated
    virtual bool deserialize(PropertyGroup & group, const std::string & filePath) { return false; }


};
    
} // namespace reflectionzeug
