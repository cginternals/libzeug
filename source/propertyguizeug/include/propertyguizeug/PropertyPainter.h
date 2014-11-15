#pragma once

#include <QStyleOptionViewItem>

#include <propertyguizeug/propertyguizeug_api.h>

class QPainter;

namespace reflectionzeug
{
    class AbstractValueProperty;
}

namespace propertyguizeug
{

class AbstractPropertyPainterPlugin;
   
class PROPERTYGUIZEUG_API PropertyPainter
{
public:
    PropertyPainter();

    void drawValue(QPainter * painter, 
                   const QStyleOptionViewItem & option,
                   reflectionzeug::AbstractValueProperty & property);
    
    void addPlugin(AbstractPropertyPainterPlugin * plugin);
    
    QPainter * painter() const;
    const QStyleOptionViewItem & option() const;

    void setDrawn();

private:
	void drawString(const QString & string);
	void drawItemViewBackground();

    bool m_drawn;
    QPainter * m_painter;
    QStyleOptionViewItem m_option;

    QList<AbstractPropertyPainterPlugin *> m_plugins;
};

} // namespace propertyguizeug
