
#pragma once

#include <sstream>
#include <fstream>
#include "AbstractPropertyVisitor.h"

namespace propertyzeug {

template <typename Type>
class Property;

class PropertyGroup;
    
/** @brief
 * Saves values of a property hierachy to a specified file.
 */
    
class PROPERTYZEUG_API PropertySerializer
{
public:
    PropertySerializer();
    virtual ~PropertySerializer();

    bool serialize(PropertyGroup & group, std::string filePath);
    
protected:
    void serializeProperty(const AbstractProperty & property);
    void serializeGroup(PropertyGroup & group);
    void pushGroupToPath(const PropertyGroup & group);
    void popGroupFromPath();

    std::fstream m_fstream;
    std::string m_currentPath;
    std::string m_previousPath;
};
    
} // namespace
