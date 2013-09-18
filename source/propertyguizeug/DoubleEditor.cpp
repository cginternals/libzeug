
#include <propertyguizeug/DoubleEditor.h>

namespace propertyguizeug {
    
DoubleEditor::DoubleEditor(Property<double> * property, QWidget * parent)
:   QDoubleSpinBox(parent)
,   m_property(property)
{
    this->setFrame(false);
    this->setValue(m_property->value());
    this->setDecimals(4);

    if (m_property->hasRanges())
        this->setRange(m_property->minimum(), m_property->maximum());
    
    this->connect(this, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                  [this](double d) {
                      m_property->setValue(d);
                  });
}
    
DoubleEditor::~DoubleEditor()
{
    
}

} // namespace
