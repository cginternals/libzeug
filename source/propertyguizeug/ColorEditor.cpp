
#include <QColorDialog>
#include <propertyguizeug/ColorEditor.h>

namespace propertyguizeug {

ColorEditor::ColorEditor(Property<Color> * property, QWidget * parent)
:   QWidget(parent)
,   m_dialog(new QColorDialog(this))
,   m_property(property)
{
    const Color & color = m_property->value();
    m_dialog->setCurrentColor(QColor(color.red(), color.green(), color.blue(), color.alpha()));
    m_dialog->setOptions(QColorDialog::NoButtons | QColorDialog::ShowAlphaChannel);
    this->connect(m_dialog, &QColorDialog::colorSelected, this, &ColorEditor::setColor);
    m_dialog->show();
}

ColorEditor::~ColorEditor()
{
}

void ColorEditor::setColor(const QColor & color)
{
    m_property->setValue(Color(color.red(), color.green(), color.blue(), color.alpha()));
}

} // namespace
