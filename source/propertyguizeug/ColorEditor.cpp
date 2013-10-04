

#include <QColorDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

#include <propertyzeug/Property.h>

#include "ColorEditor.h"
#include "ColorButton.h"

namespace zeug {

ColorEditor::ColorEditor(Property<Color> * property, QWidget * parent)
:   QWidget(parent)
,   m_property(property)
{
    const Color & color = m_property->value();
    QColor qcolor(color.red(), color.green(), color.blue(), color.alpha());
    
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->setSpacing(3);
    
    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setText(QString::fromStdString(m_property->valueAsString()));
    
    m_button = new ColorButton(qcolor, this);
    
    layout->addWidget(m_button);
    layout->addWidget(m_lineEdit);
    
    this->setFocusProxy(m_lineEdit);
    
    this->connect(m_button, &ColorButton::pressed, this, &ColorEditor::openColorPicker);
}

ColorEditor::~ColorEditor()
{
}
    
void ColorEditor::openColorPicker()
{
    QColor qcolor = QColorDialog::getColor(this->qcolor(),
                                           m_button,
                                           "Choose Color",
                                           QColorDialog::ShowAlphaChannel);
    this->setQColor(qcolor);
}
    
QColor ColorEditor::qcolor() const
{
    const Color & color = m_property->value();
    return QColor(QColor(color.red(), color.green(), color.blue(), color.alpha()));
}
    
void ColorEditor::setQColor(const QColor & qcolor)
{
    Color color(qcolor.red(), qcolor.green(), qcolor.blue(), qcolor.alpha());
    m_property->setValue(color);
    
    m_button->setColor(qcolor);
    m_lineEdit->setText(QString::fromStdString(m_property->valueAsString()));
}

} // namespace
