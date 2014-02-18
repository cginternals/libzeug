

#include <QHBoxLayout>
#include <QSpinBox>

#include <propertyzeug/Property.h>

#include "IntegerEditor.h"

namespace zeug 
{
    
IntegerEditor::IntegerEditor(Property<int> * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_spinBox(new QSpinBox(this))
,   m_property(property)
{
    boxLayout()->addWidget(m_spinBox);
    setFocusProxy(m_spinBox);

    m_spinBox->setRange(m_property->minimum(), m_property->maximum());
	
    if (m_property->hasStep())
        m_spinBox->setSingleStep(m_property->step());

    m_spinBox->setValue(m_property->value());
    
    connect(m_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                  [this](int i) {
                      m_property->setValue(i);
                  });
}
    
IntegerEditor::~IntegerEditor()
{
}

} // namespace
