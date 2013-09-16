
#pragma once

#include <string>
#include <vector>
#include <propertyzeug/propertyzeug.h>

namespace propertyzeug {

template <typename Type>
class Property;
    
class Color;
class FilePath;

class PropertyGroup;
    
/** @brief
 * Part of the Visitor Pattern implementation.
 */
    
class PROPERTYZEUG_API AbstractPropertyVisitor
{
public:
    virtual ~AbstractPropertyVisitor();

    virtual void visit(Property<bool> & property) = 0;
    virtual void visit(Property<int> & property) = 0;
    virtual void visit(Property<double> & property) = 0;
    virtual void visit(Property<std::string> & property) = 0;
    virtual void visit(Property<Color> & property) = 0;
    virtual void visit(Property<FilePath> & property) = 0;
    
    virtual void visit(Property<std::vector<bool>> & property) = 0;
    virtual void visit(Property<std::vector<int>> & property) = 0;
    virtual void visit(Property<std::vector<double>> & property) = 0;

    virtual void visit(PropertyGroup & property) = 0;

protected:

};

} // namespace