#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <reflectionzeug/AbstractPropertyDeserializer.h>

namespace reflectionzeug
{

class PropertyGroup;

/**
 * \brief Loads values of a property hierachy from an INI like file format.
 * \see IniPropertySerializer
 */
class REFLECTIONZEUG_API IniPropertyDeserializer : public AbstractPropertyDeserializer
{
public:
    IniPropertyDeserializer();
    virtual ~IniPropertyDeserializer();

    virtual bool deserialize(PropertyGroup & group, const std::string & filePath) override;

protected:
    bool isGroupDeclaration(const std::string & line);
    bool isPropertyDeclaration(const std::string & line);

    bool updateCurrentGroup(const std::string & line);
    bool setPropertyValue(const std::string & line);

protected:
    PropertyGroup * m_rootGroup;
    PropertyGroup * m_currentGroup;
    std::string m_currentValue;
};

} // namespace reflectionzeug
