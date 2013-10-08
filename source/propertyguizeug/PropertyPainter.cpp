
#include <propertyguizeug/PropertyPainter.h>

#include <QApplication>
#include <QPainter>

#include <propertyzeug/Property.h>

#include "TransparencyBackgroundBrush.hpp"

namespace zeug {
    
PropertyPainter::PropertyPainter()
:   m_drawn(false)
,   m_painter(nullptr)
{
}

PropertyPainter::~PropertyPainter()
{
}

void PropertyPainter::drawValue(QPainter * painter, 
    const QStyleOptionViewItem & option, AbstractProperty & property)
{
    m_drawn = false;
    m_painter = painter;
    m_option = option;

    property.accept(*this);

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
    
    QPixmap pixmap(20, 20);
    pixmap.fill(QColor(color.red(),
					   color.green(),
                       color.blue(),
                       color.alpha()));
    
    QRect pixmapRect = m_option.rect;
    pixmapRect.setLeft(pixmapRect.left() + 3);
    pixmapRect.setTop(pixmapRect.top() + 4);
    pixmapRect.setWidth(20);
    pixmapRect.setHeight(20);
    
    m_painter->fillRect(pixmapRect, TransparencyBackgroundBrush());
    m_painter->drawPixmap(pixmapRect, pixmap);
    
    QRect rect = m_option.rect;
    rect.setLeft(pixmapRect.right() + 6);

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

void PropertyPainter::visit(PropertyGroup & property)
{

}
    
} // namespace
