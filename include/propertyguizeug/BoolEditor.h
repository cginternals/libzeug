
#pragma once

#include <QCheckBox>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using propertyzeug::Property;
    
class PROPERTYGUIZEUG_API BoolEditor : public QCheckBox
{
public:
    BoolEditor(Property<bool> * property, QWidget * parent = nullptr);
    virtual ~BoolEditor();

protected:
    Property<bool> * m_property;
};

} // namespace
