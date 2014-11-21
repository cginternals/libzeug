#include <propertyguizeug/PropertyEditor.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QStyleOptionViewItem>

namespace propertyguizeug
{

void PropertyEditor::drawString(
    const QString & string, 
    QPainter * painter, 
    const QStyleOptionViewItem & option)
{
    auto widget = option.widget;
    auto style = widget ? widget->style() : QApplication::style();
    
    auto optionWithText = option;
    optionWithText.text = string;
    style->drawControl(QStyle::CE_ItemViewItem, &optionWithText, painter, widget);
}
	
PropertyEditor::PropertyEditor(QWidget * parent)
:	QWidget{parent}
,	m_layout{new QHBoxLayout{this}}
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
}

void PropertyEditor::addWidget(QWidget * widget)
{
    m_layout->addWidget(widget);
}

QHBoxLayout * PropertyEditor::boxLayout()
{
	return m_layout;
}

} // namespace propertyguizeug
