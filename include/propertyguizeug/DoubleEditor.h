
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QDoubleSpinBox>

namespace propertyzeug {
    template <typename Type>
    class Property;
}

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
