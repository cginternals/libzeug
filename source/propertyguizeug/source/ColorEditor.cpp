
#include <QColorDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QRegExpValidator>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/ColorEditor.h>

#include "ColorButton.h"

using namespace reflectionzeug;
namespace propertyguizeug
{

ColorEditor::ColorEditor(Property<Color> * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_property(property)
{
    const Color & color = m_property->value();
    QColor qcolor(color.red(), color.green(), color.blue(), color.alpha());
    
    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
    
    m_button = new ColorButton(qcolor, this);
    
    this->boxLayout()->addWidget(m_button);
    this->boxLayout()->addWidget(m_lineEdit);
    
    this->setFocusProxy(m_lineEdit);

    QRegExpValidator * validator = new QRegExpValidator(QRegExp("#[0-9A-Fa-f]{8}"), this);
    m_lineEdit->setValidator(validator);
    
    this->connect(m_button, &ColorButton::pressed, this, &ColorEditor::openColorPicker);
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &ColorEditor::parseColor);
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
    if (qcolor.isValid())
        this->setQColor(qcolor);
}

void ColorEditor::parseColor()
{
    QString text = m_lineEdit->text();
    text.remove('#');

    Color color(text.toUInt(0, 16));
    this->setColor(color);
}
    
QColor ColorEditor::qcolor() const
{
    const Color & color = m_property->value();
    return QColor(color.red(), color.green(), color.blue(), color.alpha());
}
    
void ColorEditor::setQColor(const QColor & qcolor)
{
    Color color(qcolor.red(), qcolor.green(), qcolor.blue(), qcolor.alpha());
    m_property->setValue(color);
    
    m_button->setColor(qcolor);
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
}

void ColorEditor::setColor(const Color & color)
{
    QColor qcolor(color.red(), color.green(), color.blue(), color.alpha());
    m_property->setValue(color);

    m_button->setColor(qcolor);
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
}

} // namespace propertyguizeug
