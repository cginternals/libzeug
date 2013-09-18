
#pragma once

#include <QDoubleSpinBox>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using propertyzeug::Property;

class PROPERTYGUIZEUG_API DoubleEditor : public QDoubleSpinBox
{
public:
    DoubleEditor(Property<double> * property, QWidget * parent = nullptr);
    virtual ~DoubleEditor();

protected:
    Property<double> * m_property;
};

} // namespace
