
#pragma once

#include <QStyleOptionViewItem>

#include <propertyguizeug/propertyguizeug.h>

#include <reflectionzeug/AbstractPropertyVisitor.h>


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
   
class PROPERTYGUIZEUG_API PropertyPainter : public reflectionzeug::AbstractPropertyVisitor
{
public:
    PropertyPainter();
    virtual ~PropertyPainter();

    void drawValue(QPainter * painter, 
                   const QStyleOptionViewItem & option,
                   reflectionzeug::ValueProperty & property);

    virtual void visit(reflectionzeug::Property<bool> & property);
    virtual void visit(reflectionzeug::Property<int> & property);
    virtual void visit(reflectionzeug::Property<double> & property);
    virtual void visit(reflectionzeug::Property<std::string> & property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::Color> & property);
    virtual void visit(reflectionzeug::Property<reflectionzeug::FilePath> & property);
    
    virtual void visit(reflectionzeug::Property<std::vector<bool>> & property);
    virtual void visit(reflectionzeug::Property<std::vector<int>> & property);
    virtual void visit(reflectionzeug::Property<std::vector<double>> & property);
    virtual void visit(reflectionzeug::Property<std::set<int>> & property);
    
protected:
	void drawString(const QString & string);
	void drawItemViewBackground();

    bool m_drawn;
    QPainter * m_painter;
    QStyleOptionViewItem m_option;
    
};

} // namespace propertyguizeug
