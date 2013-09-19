
#include <propertyguizeug/BoolEditor.h>

namespace propertyguizeug {
    
BoolEditor::BoolEditor(Property<bool> * property, QWidget * parent)
:   QCheckBox(parent)
,   m_property(property)
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setCheckState(property->value() ? Qt::Checked : Qt::Unchecked);
    this->connect(this, &QCheckBox::stateChanged,
                  [this](int state) {
                      if (state == Qt::Unchecked)
                          m_property->setValue(false);
                      else
                          m_property->setValue(true);
                  });
}
    
BoolEditor::~BoolEditor()
{
    
}

} // namespace
