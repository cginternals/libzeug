#include <propertyguizeug/PropertyPainter.h>

#include <QApplication>
#include <QPainter>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/BoolEditor.h>
#include <propertyguizeug/ColorEditor.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyPainter::PropertyPainter()
:   m_drawn(false)
,   m_painter(nullptr)
{
}

void PropertyPainter::drawValue(QPainter * painter, 
    const QStyleOptionViewItem & option, AbstractValueProperty & property)
{
    m_drawn = false;
    m_painter = painter;
    m_option = option;
    
    drawItemViewBackground();
    property.accept(this);

    if (!m_drawn)
    {
        auto prefix = property.option<std::string>("prefix", "");
        auto suffix = property.option<std::string>("suffix", "");
        this->drawString(QString::fromStdString(prefix + property.toString() + suffix));
    }
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
    
void PropertyPainter::visit(reflectionzeug::AbstractValueProperty * property)
{
}

void PropertyPainter::visit(Property<bool> * property)
{
    BoolEditor::paint(m_painter, m_option, *property);
    m_drawn = true;
}

void PropertyPainter::visit(ColorPropertyInterface * property)
{
    ColorEditor::paint(m_painter, m_option, *property);
    m_drawn = true;
}
    
} // namespace propertyguizeug
