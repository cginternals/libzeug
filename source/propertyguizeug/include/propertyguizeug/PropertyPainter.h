#pragma once

#include <QStyleOptionViewItem>

#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/PropertyVisitor.h>

#include <propertyguizeug/propertyguizeug_api.h>

class QPainter;

namespace reflectionzeug 
{
    class AbstractValueProperty;
    class ColorPropertyInterface;
}

namespace propertyguizeug
{
   
class PROPERTYGUIZEUG_API PropertyPainter : 
    public reflectionzeug::PropertyVisitor<
        reflectionzeug::AbstractValueProperty, 
        reflectionzeug::Property<bool>, 
        reflectionzeug::ColorPropertyInterface>
{
public:
    PropertyPainter();

    void drawValue(QPainter * painter, 
                   const QStyleOptionViewItem & option,
                   reflectionzeug::AbstractValueProperty & property);

    virtual void visit(reflectionzeug::AbstractValueProperty * property);
    virtual void visit(reflectionzeug::Property<bool> * property);
    virtual void visit(reflectionzeug::ColorPropertyInterface * property);
    
private:
	void drawString(const QString & string);
	void drawItemViewBackground();

    bool m_drawn;
    QPainter * m_painter;
    QStyleOptionViewItem m_option;
};

} // namespace propertyguizeug
