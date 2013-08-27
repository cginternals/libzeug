
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
    virtual void visit(Property<unsigned int> & property) = 0;
    virtual void visit(Property<long> & property) = 0;
    virtual void visit(Property<unsigned long> & property) = 0;
    virtual void visit(Property<char> & property) = 0;
    virtual void visit(Property<unsigned char> & property) = 0;
    virtual void visit(Property<float> & property) = 0;
    virtual void visit(Property<double> & property) = 0;
    virtual void visit(Property<std::string> & property) = 0;
    virtual void visit(Property<Color> & property) = 0;
    virtual void visit(Property<FilePath> & property) = 0;
    
    virtual void visit(Property<std::vector<bool>> & property) {};
    virtual void visit(Property<std::vector<int>> & property) {};
    virtual void visit(Property<std::vector<float>> & property) {};
    virtual void visit(Property<std::vector<double>> & property) {};

    virtual void visit(PropertyGroup & property) = 0;

protected:

};

} // namespace