
#include "BoolEditor.h"

#include <propertyzeug/Property.h>

namespace zeug {
    
BoolEditor::BoolEditor(Property<bool> * property, QWidget * parent)
:   QCheckBox(parent)
,   m_property(property)
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setCheckState(property->value() ? Qt::Checked : Qt::Unchecked);
    this->connect(this, &QCheckBox::stateChanged,
                  [this](int state) {
                      m_property->setValue(state == Qt::Checked);
                  });
}
    
BoolEditor::~BoolEditor()
{
    
}

} // namespace
