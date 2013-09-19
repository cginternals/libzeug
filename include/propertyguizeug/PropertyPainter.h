
#pragma once

#include <propertyzeug/AbstractPropertyVisitor.h>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

class QWidget;

namespace propertyguizeug {

using namespace propertyzeug;
    
class PROPERTYGUIZEUG_API PropertyPainter : public AbstractPropertyVisitor
{
public:
    PropertyPainter();
    virtual ~PropertyPainter();

    bool drawValue(QPainter * painter, 
                   const QStyleOptionViewItem & option,
                   AbstractProperty & property);

    virtual void visit(Property<bool> & property);
    virtual void visit(Property<int> & property);
    virtual void visit(Property<double> & property);
    virtual void visit(Property<std::string> & property);
    virtual void visit(Property<Color> & property);
    virtual void visit(Property<FilePath> & property);
    
    virtual void visit(Property<std::vector<bool>> & property);
    virtual void visit(Property<std::vector<int>> & property);
    virtual void visit(Property<std::vector<double>> & property);

    virtual void visit(PropertyGroup & property);
    
protected:
    bool m_drawn;
    QPainter * m_painter;
    QStyleOptionViewItem m_option;
    
};

} // namespace
