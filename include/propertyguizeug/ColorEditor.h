
#pragma once

#include <QWidget>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using namespace propertyzeug;
    
class PROPERTYGUIZEUG_API ColorEditor : public QWidget
{
    Q_OBJECT

public:
    ColorEditor(Property<Color> * property, QWidget * parent = nullptr);
    virtual ~ColorEditor();

protected:
    Property<Color> * m_property;
};

} // namespace
