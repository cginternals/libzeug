
#pragma once

#include "AbstractPropertyVisitor.h"

namespace propertyzeug {
    
class PROPERTYZEUG_API PropertySerializer : public AbstractPropertyVisitor
{
public:
    PropertySerializer();
    virtual ~PropertySerializer();

    virtual void visit(Property<bool> & property);
    virtual void visit(Property<int> & property);
    virtual void visit(Property<unsigned int> & property);
    virtual void visit(Property<long> & property);
    virtual void visit(Property<unsigned long> & property);
    virtual void visit(Property<char> & property);
    virtual void visit(Property<unsigned char> & property);
    virtual void visit(Property<float> & property);
    virtual void visit(Property<double> & property);
    virtual void visit(Property<std::string> & property);
    virtual void visit(Property<Color> & property);
    virtual void visit(Property<FilePath> & property);

    virtual void visit(PropertyGroup & property);

    bool serialize(PropertyGroup & group, std::string filePath);
    
protected:

};

} // namespace