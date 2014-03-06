
#pragma once

#include <QStyleOptionViewItem>

#include <propertyguizeug/propertyguizeug.h>

#include <reflectionzeug/StandardPropertyVisitor.h>


class QPainter;
namespace reflectionzeug {
    template <typename Type>
    class Property;
    class ValueProperty;
    class Color;
    class FilePath;
}


namespace propertyguizeug
{
   
class PROPERTYGUIZEUG_API PropertyPainter : public reflectionzeug::PropertyVisitor<bool, reflectionzeug::Color>
{
public:
    PropertyPainter();
    virtual ~PropertyPainter();

    void drawValue(QPainter * painter, 
                   const QStyleOptionViewItem & option,
                   reflectionzeug::ValueProperty & property);

    virtual void visit(reflectionzeug::Property<bool> * property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::Color> * property);
    
protected:
	void drawString(const QString & string);
	void drawItemViewBackground();

    bool m_drawn;
    QPainter * m_painter;
    QStyleOptionViewItem m_option;
    
};

} // namespace propertyguizeug
