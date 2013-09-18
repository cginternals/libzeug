
#include <propertyguizeug/IntegerEditor.h>

namespace propertyguizeug {
    
IntegerEditor::IntegerEditor(Property<int> * property, QWidget * parent)
:   QSpinBox(parent)
,   m_property(property)
{
    this->setFrame(false);
    this->setValue(m_property->value());

    if (m_property->hasRanges())
        this->setRange(m_property->minimum(), m_property->maximum());
    
    this->connect(this, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                  [this](int i) {
                      m_property->setValue(i);
                  });
}
    
IntegerEditor::~IntegerEditor()
{
    
}

} // namespace
