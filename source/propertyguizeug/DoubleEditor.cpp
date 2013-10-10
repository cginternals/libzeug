
#include "DoubleEditor.h"

#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <propertyzeug/Property.h>

namespace zeug {
    
DoubleEditor::DoubleEditor(Property<double> * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_spinBox(new QDoubleSpinBox(this))
,   m_property(property)
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(1, 0, 3, 0);
    layout->setSpacing(3);
    
    layout->addWidget(m_spinBox);
    
    m_spinBox->setValue(m_property->value());
    m_spinBox->setDecimals(4);
    
    this->setFocusProxy(m_spinBox);

    if (m_property->hasRanges())
        m_spinBox->setRange(m_property->minimum(), m_property->maximum());
    
    this->connect(m_spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                  [this](double d) {
                      m_property->setValue(d);
                  });
}
    
DoubleEditor::~DoubleEditor()
{
    
}

} // namespace
