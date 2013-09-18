
#pragma once

#include <QSpinBox>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using namespace propertyzeug;

template <typename Number>
class PROPERTYGUIZEUG_API IntegerEditor : public QSpinBox
{
public:
    IntegerEditor(Property<Number> * property, QWidget * parent = nullptr);
    virtual ~IntegerEditor();

protected:
    Property<Number> * m_property;
};

template <typename Number>
IntegerEditor<Number>::IntegerEditor(Property<Number> * property, QWidget * parent)
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
    
template <typename Number>
IntegerEditor<Number>::~IntegerEditor()
{
    
}

} // namespace
