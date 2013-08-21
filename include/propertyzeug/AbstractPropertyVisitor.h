
#pragma once

namespace propertyzeug {

template <typename Type>
class Property;

class PropertyGroup;
    
class PROPERTYZEUG_API AbstractPropertyVisitor
{
public:
    virtual ~AbstractPropertyVisitor() {};

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

    virtual void visit(PropertyGroup & property) = 0;
};

} // namespace
