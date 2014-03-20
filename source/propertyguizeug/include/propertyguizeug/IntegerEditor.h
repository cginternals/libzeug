
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>

class QSpinBox;

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API IntegerEditor : public PropertyEditor
{
public:
    IntegerEditor(reflectionzeug::Property<int> * property, QWidget * parent = nullptr);
    virtual ~IntegerEditor();

protected:
    QSpinBox * m_spinBox;
    
    reflectionzeug::Property<int> * m_property;
};

} // namespace propertyguizeug
