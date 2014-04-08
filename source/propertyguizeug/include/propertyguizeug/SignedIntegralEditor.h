
#pragma once

#include <propertyguizeug/PropertyEditor.h>


namespace reflectionzeug
{
    class SignedIntegralPropertyInterface;
}

namespace propertyguizeug
{
    
class LongLongSpinBox;

class PROPERTYGUIZEUG_API SignedIntegralEditor : public PropertyEditor
{
public:
    SignedIntegralEditor(reflectionzeug::SignedIntegralPropertyInterface * property, 
                           QWidget * parent = nullptr);

    virtual ~SignedIntegralEditor();

protected:
    LongLongSpinBox * m_spinBox;
    
    reflectionzeug::SignedIntegralPropertyInterface * m_property;
};

} // namespace propertyguizeug
