
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
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(1, 0, 3, 0);
    layout->setSpacing(3);
    
    layout->addWidget(m_spinBox);
    
    m_spinBox->setValue(m_property->value());
    
    this->setFocusProxy(m_spinBox);

    if (m_property->hasRanges())
        m_spinBox->setRange(m_property->minimum(), m_property->maximum());
    
    this->connect(m_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                  [this](int i) {
                      m_property->setValue(i);
                  });
}
    
IntegerEditor::~IntegerEditor()
{
    
}

} // namespace
