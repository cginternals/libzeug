
#pragma once

#include <propertyguizeug/PropertyEditor.h>


namespace reflectionzeug
{
    class UnsignedIntegralPropertyInterface;
}

namespace propertyguizeug
{
    
class ULongLongSpinBox;

/** \brief Editor for signed integral point properties
 *
 * Supported options
 * - _minimum (unsigned long long)_: lowest value to be accepted
 * - _maximum (unsigned long long)_: greatest value to be accepted
 * - _step (unsigned long long)_: step size of the spinbox
 */
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
