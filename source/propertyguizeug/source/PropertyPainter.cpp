#include <propertyguizeug/PropertyPainter.h>

#include <cassert>

#include <QApplication>
#include <QPainter>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/BoolEditor.h>
#include <propertyguizeug/ColorEditor.h>
#include <propertyguizeug/FloatingPointEditor.h>
#include <propertyguizeug/PropertyPainterPlugin.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyPainter::PropertyPainter()
:   m_drawn{false}
,   m_painter{nullptr}
{
    addPlugin(new PropertyPainterPlugin<
        BoolEditor, 
        ColorEditor, 
        FloatingPointEditor>{});
}

void PropertyPainter::drawValue(QPainter * painter, 
    const QStyleOptionViewItem & option, AbstractValueProperty & property)
{
    m_drawn = false;
    m_painter = painter;
    m_option = option;
    
    drawItemViewBackground();

    for (auto plugin : m_plugins)
    {
        property.accept(plugin);

        if (m_drawn)
            break;
    }

    if (!m_drawn)
        this->drawString(QString::fromStdString(property.toString()));
}

void PropertyPainter::addPlugin(AbstractPropertyPainterPlugin * plugin)
{
    assert(plugin);
    plugin->setPainter(this);
    m_plugins.prepend(plugin);
}

QPainter * PropertyPainter::painter() const
{
    return m_painter;
}

const QStyleOptionViewItem & PropertyPainter::option() const
{
    return m_option;
}

void PropertyPainter::setDrawn()
{
    m_drawn = true;
}

void PropertyPainter::drawString(const QString & string)
{
    auto widget = m_option.widget;
    auto style = widget ? widget->style() : QApplication::style();

    m_option.text = string;
    style->drawControl(QStyle::CE_ItemViewItem, &m_option, m_painter, widget);
}

void PropertyPainter::drawItemViewBackground()
{
    auto widget = m_option.widget;
    auto style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &m_option, m_painter, widget);
}
    
} // namespace propertyguizeug
