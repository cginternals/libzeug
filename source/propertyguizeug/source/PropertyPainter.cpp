
#include <QApplication>
#include <QPainter>

#include <reflectionzeug/Property.h>

#include "PropertyEditor.h"
#include "ColorButton.h"

#include <propertyguizeug/PropertyPainter.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyPainter::PropertyPainter()
:   m_drawn(false)
,   m_painter(nullptr)
{
}

PropertyPainter::~PropertyPainter()
{
}

void PropertyPainter::drawValue(QPainter * painter, 
    const QStyleOptionViewItem & option, ValueProperty & property)
{
    m_drawn = false;
    m_painter = painter;
    m_option = option;

    handle(property);

	if (!m_drawn)
		this->drawString(QString::fromStdString(property.valueAsString()));
}

void PropertyPainter::drawString(const QString & string)
{
	const QWidget * widget = m_option.widget;
	QStyle * style = widget ? widget->style() : QApplication::style();

	m_option.text = string;
	style->drawControl(QStyle::CE_ItemViewItem, &m_option, m_painter, widget);
}

void PropertyPainter::drawItemViewBackground()
{
	const QWidget * widget = m_option.widget;
	QStyle * style = widget ? widget->style() : QApplication::style();
	style->drawControl(QStyle::CE_ItemViewItem, &m_option, m_painter, widget);
}

void PropertyPainter::visit(Property<bool> & property)
{
	this->drawItemViewBackground();

    QStyleOptionButton opt;
    opt.state = property.value() ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    opt.rect = m_option.rect;
    opt.rect.setLeft(opt.rect.left() + PropertyEditor::s_horizontalMargin);

	const QWidget * widget = m_option.widget;
	QStyle * style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_CheckBox, &opt, m_painter, widget);
    
    m_drawn = true;
}
    
void PropertyPainter::visit(Property<int> & property)
{

}
    
void PropertyPainter::visit(Property<double> & property)
{

}
    
void PropertyPainter::visit(Property<std::string> & property)
{

}

void PropertyPainter::visit(Property<Color> & property)
{
	this->drawItemViewBackground();
    
    const Color & color = property.value();

    QColor qcolor(color.red(),
                  color.green(),
                  color.blue(),
                  color.alpha());
    QPoint topLeft(m_option.rect.left() + PropertyEditor::s_horizontalMargin, 
                   m_option.rect.top() + 4);

    ColorButton::paint(m_painter, topLeft, qcolor);
    
    QRect rect = m_option.rect;
    rect.setLeft(m_option.rect.left() + 
                 PropertyEditor::s_horizontalMargin + 
                 ColorButton::s_fixedSize.width() + 
                 PropertyEditor::s_spacing * 2);

    const QWidget * widget = m_option.widget;
    QStyle * style = widget ? widget->style() : QApplication::style();
    style->drawItemText(m_painter,
                        rect,
                        Qt::AlignVCenter,
                        m_option.palette,
                        true,
                        QString::fromStdString(property.valueAsString()),
                        QPalette::Text);
    
    m_drawn = true;
}

void PropertyPainter::visit(Property<FilePath> & property)
{

}

void PropertyPainter::visit(Property<std::vector<bool>> & property)
{

}

void PropertyPainter::visit(Property<std::vector<int>> & property)
{

}

void PropertyPainter::visit(Property<std::vector<double>> & property)
{

}

void PropertyPainter::visit(Property<std::set<int>> & property)
{

}
    
} // namespace propertyguizeug
