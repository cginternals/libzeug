
#pragma once

#include <propertyzeug/AbstractPropertyVisitor.h>
#include "propertyguizeug.h"

class QWidget;

namespace propertyguizeug {

using namespace propertyzeug;
    
class PROPERTYGUIZEUG_API WidgetBuilder : public AbstractPropertyVisitor
{
public:
    WidgetBuilder();
    virtual ~WidgetBuilder();
    
    QWidget * build(PropertyGroup & group);
    
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
    
    virtual void visit(Property<std::vector<bool>> & property);
    virtual void visit(Property<std::vector<int>> & property);
    virtual void visit(Property<std::vector<float>> & property);
    virtual void visit(Property<std::vector<double>> & property);
    
    virtual void visit(PropertyGroup & property);
private:
    
};

} // namespace