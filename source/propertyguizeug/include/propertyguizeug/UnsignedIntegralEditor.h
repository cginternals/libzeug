
#pragma once

#include <propertyguizeug/PropertyEditor.h>


namespace reflectionzeug
{
    class UnsignedIntegralPropertyInterface;
}

namespace propertyguizeug
{
    
class ULongLongSpinBox;

class PROPERTYGUIZEUG_API UnsignedIntegralEditor : public PropertyEditor
{
public:
    UnsignedIntegralEditor(reflectionzeug::UnsignedIntegralPropertyInterface * property, 
                           QWidget * parent = nullptr);

    virtual ~UnsignedIntegralEditor();

protected:
    ULongLongSpinBox * m_spinBox;
    
    reflectionzeug::UnsignedIntegralPropertyInterface * m_property;
};

} // namespace propertyguizeug
