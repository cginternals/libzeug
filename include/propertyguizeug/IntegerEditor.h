
#pragma once

#include <QSpinBox>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using namespace propertyzeug;

class PROPERTYGUIZEUG_API IntegerEditor : public QSpinBox
{
public:
    IntegerEditor(Property<int> * property, QWidget * parent = nullptr);
    virtual ~IntegerEditor();

protected:
    Property<int> * m_property;
};

} // namespace
