
#include "IntegerEditor.h"

#include <QHBoxLayout>
#include <QSpinBox>
#include <propertyzeug/Property.h>

namespace zeug {
    
IntegerEditor::IntegerEditor(Property<int> * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_spinBox(new QSpinBox(this))
,   m_property(property)
{
    this->boxLayout()->addWidget(m_spinBox);
    this->setFocusProxy(m_spinBox);

    if (m_property->hasRanges())
        m_spinBox->setRange(m_property->minimum(), m_property->maximum());

    m_spinBox->setValue(m_property->value());
    
    this->connect(m_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                  [this](int i) {
                      m_property->setValue(i);
                  });
}
    
IntegerEditor::~IntegerEditor()
{
    
}

} // namespace
