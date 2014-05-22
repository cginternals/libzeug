
#include <QApplication>
#include <QPainter>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/PropertyEditor.h>

#include <propertyguizeug/ColorButton.h>
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
    const QStyleOptionViewItem & option, AbstractValueProperty & property)
{
    m_drawn = false;
    m_painter = painter;
    m_option = option;

    property.accept(this);

	if (!m_drawn)
		this->drawString(QString::fromStdString(property.toString()));
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
    
void PropertyPainter::visit(reflectionzeug::AbstractValueProperty * property)
{
    m_drawn = false;
}

void PropertyPainter::visit(Property<bool> * property)
{
	this->drawItemViewBackground();

    QStyleOptionButton opt;
    opt.state = property->value() ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    opt.rect = m_option.rect;
    opt.rect.setLeft(opt.rect.left()/* + PropertyEditor::s_horizontalMargin */);

	const QWidget * widget = m_option.widget;
	QStyle * style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_CheckBox, &opt, m_painter, widget);
    
    m_drawn = true;
}

void PropertyPainter::visit(Property<Color> * property)
{
	this->drawItemViewBackground();
    
    const Color & color = property->value();

    QColor qcolor(color.red(),
                  color.green(),
                  color.blue(),
                  color.alpha());
    QPoint topLeft(m_option.rect.left(), 
                   m_option.rect.top() + 4);

    ColorButton::paint(m_painter, topLeft, qcolor);
    
    QRect rect = m_option.rect;
    rect.setLeft(m_option.rect.left() + 
                 ColorButton::s_fixedSize.width() + 2);

    const QWidget * widget = m_option.widget;
    QStyle * style = widget ? widget->style() : QApplication::style();
    style->drawItemText(m_painter,
                        rect,
                        Qt::AlignVCenter,
                        m_option.palette,
                        true,
                        QString::fromStdString(property->toString()),
                        QPalette::Text);
    
    m_drawn = true;
}
    
} // namespace propertyguizeug
