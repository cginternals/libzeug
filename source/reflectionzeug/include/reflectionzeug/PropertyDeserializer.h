
#pragma once

namespace reflectionzeug
{

class PropertyGroup;

/** \brief Loads property values from a given file.
 */
class REFLECTIONZEUG_API PropertyDeserializer
{
public:
    PropertyDeserializer();
    virtual ~PropertyDeserializer();

    bool deserialize(PropertyGroup & group, std::string filePath);

protected:
    bool isGroupDeclaration(const std::string line);
    bool isPropertyDeclaration(const std::string line);

    bool updateCurrentGroup(const std::string line);
    bool setPropertyValue(const std::string line);

protected:
    PropertyGroup * m_rootGroup;
    PropertyGroup * m_currentGroup;
    std::string m_currentValue;

};

} // namespace reflectionzeug
