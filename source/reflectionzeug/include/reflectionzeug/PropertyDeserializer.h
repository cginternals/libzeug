
#pragma once

#include <functional>
#include <sstream>

#include <reflectionzeug/AbstractPropertyVisitor.h>

namespace reflectionzeug
{

class PropertyGroup;
    
/** \brief Loads property values from a given file.
 */
class REFLECTIONZEUG_API PropertyDeserializer : public AbstractPropertyVisitor
{
public:
    PropertyDeserializer();
    virtual ~PropertyDeserializer();

    virtual void visitBool(Property<bool> & property);
    virtual void visitInt(Property<int> & property);
    virtual void visitDouble(Property<double> & property);
    virtual void visitString(Property<std::string> & property);
    virtual void visitColor(Property<Color> & property);
    virtual void visitFilePath(Property<FilePath> & property);

    virtual void visitBoolVector(Property<std::vector<bool>> & property);
    virtual void visitIntVector(Property<std::vector<int>> & property);
    virtual void visitDoubleVector(Property<std::vector<double>> & property);
    virtual void visitIntSet(Property<std::set<int>> & property);

    bool deserialize(PropertyGroup & group, std::string filePath);
    
protected:
    void deserializeVectorValues(const std::string & valueRegexString, int size,
                                 const std::function<void(const std::string &)> & functor);
    void deserializeSetValues(const std::string & valueRegexString,
                                 const std::function<void(const std::string &)> & functor);
    
    template <typename Type>
    Type convertString(const std::string & value);
    
    bool isGroupDeclaration(const std::string line);
    bool isPropertyDeclaration(const std::string line);
    
    bool updateCurrentGroup(const std::string line);
    bool setPropertyValue(const std::string line);
    
    PropertyGroup * m_rootGroup;
    PropertyGroup * m_currentGroup;
    std::string m_currentValue;
};
    
template <typename Type>
Type PropertyDeserializer::convertString(const std::string & stringValue)
{
    std::stringstream stream(stringValue);
    Type value;
    stream >> value;
    return value;
}

} // namespace reflectionzeug
