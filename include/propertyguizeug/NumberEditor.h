
#pragma once

#include <QSpinbox>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using namespace propertyzeug;

template <typename Number>
class PROPERTYGUIZEUG_API NumberEditor : public QSpinBox
{
public:
    NumberEditor(Property<Number> * property, QWidget * parent = nullptr);
    virtual ~NumberEditor();

protected:
    Property<Number> * m_property;
};

template <typename Number>
NumberEditor<Number>::NumberEditor(Property<Number> * property, QWidget * parent)
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
NumberEditor<Number>::~NumberEditor()
{
    
}

} // namespace
