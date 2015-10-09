#include <propertyguizeug/PropertyPainter.h>

#include <cassert>

#include <QApplication>
#include <QPainter>

#include <reflectionzeug/property/Property.h>

#include <propertyguizeug/BoolEditor.h>
#include <propertyguizeug/ColorEditor.h>
#include <propertyguizeug/FloatingPointEditor.h>
#include <propertyguizeug/SignedIntegralEditor.h>
#include <propertyguizeug/UnsignedIntegralEditor.h>
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
        FloatingPointEditor,
        SignedIntegralEditor,
        UnsignedIntegralEditor>{});
}

void PropertyPainter::drawValue(QPainter * painter, 
    const QStyleOptionViewItem & option, AbstractProperty & property)
{
    m_drawn = false;
    m_painter = painter;
    m_option = option;

    for (auto plugin : m_plugins)
    {
        property.accept(plugin);

        if (m_drawn)
            break;
    }

    // Fallback to default (draw string)
    if (!m_drawn) {
        this->drawString(QString::fromStdString(property.toString()));
    }
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

	style->drawItemText(
		m_painter,
		m_option.rect,
		Qt::AlignVCenter,
		m_option.palette,
		true,
		string,
		QPalette::Text);
}
    
} // namespace propertyguizeug
