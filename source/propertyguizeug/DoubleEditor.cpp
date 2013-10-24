
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
    boxLayout()->addWidget(m_spinBox);
    setFocusProxy(m_spinBox);

    m_spinBox->setRange(m_property->minimum(), m_property->maximum());
	
    if (m_property->hasStep())
	m_spinBox->setSingleStep(m_property->step());
    
    m_spinBox->setDecimals(m_property->hasPrecision() ? m_property->precision() : 3);
    m_spinBox->setValue(m_property->value());
    
    connect(m_spinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                  [this](double d) {
                      m_property->setValue(d);
                  });
}
    
DoubleEditor::~DoubleEditor()
{
}

} // namespace
