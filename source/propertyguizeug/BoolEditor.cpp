

#include <QCheckBox>
#include <QBoxLayout>

#include <propertyzeug/Property.h>

#include "BoolEditor.h"

namespace zeug 
{
    
BoolEditor::BoolEditor(Property<bool> * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_property(property)
{
    QCheckBox * checkBox = new QCheckBox(this);

    this->boxLayout()->addWidget(checkBox);
    this->setFocusProxy(checkBox);

    checkBox->setFocusPolicy(Qt::StrongFocus);
    checkBox->setCheckState(property->value() ? Qt::Checked : Qt::Unchecked);
    this->connect(checkBox, &QCheckBox::stateChanged,
                  [this](int state) {
                      m_property->setValue(state == Qt::Checked);
                  });
}
    
BoolEditor::~BoolEditor()
{
    
}

} // namespace
