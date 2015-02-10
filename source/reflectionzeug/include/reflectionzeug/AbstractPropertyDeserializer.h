#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <string>

namespace reflectionzeug
{

class PropertyGroup;

/**
 * \brief Interface for Property Deserialization Classes.
 * \see AbstractPropertySerializer
 */

class REFLECTIONZEUG_API AbstractPropertyDeserializer
{
public:
    AbstractPropertyDeserializer();
    virtual ~AbstractPropertyDeserializer();

    virtual bool deserialize(PropertyGroup & group, const std::string & filePath) = 0;

};

} // namespace reflectionzeug
