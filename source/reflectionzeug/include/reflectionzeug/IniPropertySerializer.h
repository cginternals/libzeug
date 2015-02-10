#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <reflectionzeug/AbstractPropertySerializer.h>

#include <deque>
#include <fstream>

namespace reflectionzeug
{

class AbstractValueProperty;
class PropertyGroup;
    
/**
 * \brief Saves values of a property hierachy in an INI like file format.
 * \see IniPropertyDeserializer
 */
    
class REFLECTIONZEUG_API IniPropertySerializer : public AbstractPropertySerializer
{
public:
    IniPropertySerializer();
    virtual ~IniPropertySerializer();

    virtual bool serialize(PropertyGroup & group, const std::string & filePath) override;
    
protected:
    void serializeValue(const AbstractValueProperty & property);
    void serializeGroup(const PropertyGroup & group);
    
    void pushGroupToPath(const PropertyGroup & group);
    void popGroupFromPath();
    std::string currentPath() const;

protected:
    std::fstream m_fstream;
    std::deque<std::string> m_pathStack;
};
    
} // namespace reflectionzeug
