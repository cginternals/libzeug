
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QStyleOptionViewItem>

#include <propertyzeug/AbstractPropertyVisitor.h>

class QPainter;

namespace zeug {

template <typename Type>
class Property;
class ValueProperty;

class Color;
class FilePath;
    
class PROPERTYGUIZEUG_API PropertyPainter : public AbstractPropertyVisitor
{
public:
    PropertyPainter();
    virtual ~PropertyPainter();

    void drawValue(QPainter * painter, 
                   const QStyleOptionViewItem & option,
                   ValueProperty & property);

    virtual void visit(Property<bool> & property);
    virtual void visit(Property<int> & property);
    virtual void visit(Property<double> & property);
    virtual void visit(Property<std::string> & property);
    virtual void visit(Property<Color> & property);
    virtual void visit(Property<FilePath> & property);
    
    virtual void visit(Property<std::vector<bool>> & property);
    virtual void visit(Property<std::vector<int>> & property);
    virtual void visit(Property<std::vector<double>> & property);
    virtual void visit(Property<std::set<int>> & property);
    
protected:
	void drawString(const QString & string);
	void drawItemViewBackground();

    bool m_drawn;
    QPainter * m_painter;
    QStyleOptionViewItem m_option;
    
};

} // namespace zeug
