
#pragma once

#include <functional>
#include <sstream>

#include <reflectionzeug/StandardPropertyVisitor.h>

namespace reflectionzeug
{

class PropertyGroup;
    
/** \brief Loads property values from a given file.
 */
class REFLECTIONZEUG_API PropertyDeserializer : public StandardPropertyVisitor
{
public:
    PropertyDeserializer();
    virtual ~PropertyDeserializer();

    bool deserialize(PropertyGroup & group, std::string filePath);
    
protected:
    virtual void visit(Property<bool> * property);
    virtual void visit(Property<int> * property);
    virtual void visit(Property<double> * property);
    virtual void visit(Property<std::string> * property);
    virtual void visit(Property<Color> * property);
    virtual void visit(Property<FilePath> * property);
    
    virtual void visit(Property<std::vector<bool>> * property);
    virtual void visit(Property<std::vector<int>> * property);
    virtual void visit(Property<std::vector<double>> * property);
    virtual void visit(Property<std::set<int>> * property);

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
    
protected:
    PropertyGroup * m_rootGroup;
    PropertyGroup * m_currentGroup;
    std::string m_currentValue;
    
};

} // namespace reflectionzeug

#include "PropertyDeserializer.hpp"
