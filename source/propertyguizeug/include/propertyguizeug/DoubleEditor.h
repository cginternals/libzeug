
#pragma once

#include <propertyguizeug/PropertyEditor.h>

class QDoubleSpinBox;

namespace reflectionzeug
{
    template <typename Type>
    class Property;
}

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API DoubleEditor : public PropertyEditor
{
public:
    DoubleEditor(reflectionzeug::Property<double> * property, QWidget * parent = nullptr);
    virtual ~DoubleEditor();

protected:
    QDoubleSpinBox * m_spinBox;
    
    reflectionzeug::Property<double> * m_property;
};

} // namespace propertyguizeug
