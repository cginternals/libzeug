
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>

class QDoubleSpinBox;

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API FloatingPointEditor : public PropertyEditor
{
public:
    FloatingPointEditor(reflectionzeug::FloatingPointPropertyInterface * property, QWidget * parent = nullptr);
    virtual ~FloatingPointEditor();

protected:
    QDoubleSpinBox * m_spinBox;
    
    reflectionzeug::FloatingPointPropertyInterface * m_property;
};

} // namespace propertyguizeug
