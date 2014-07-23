
#pragma once

#include <propertyguizeug/PropertyEditor.h>


namespace reflectionzeug
{
    class SignedIntegralPropertyInterface;
}

namespace propertyguizeug
{
    
class LongLongSpinBox;

/** \brief Editor for signed integral point properties
 *
 * Supported options
 * - _minimum (long long)_: lowest value to be accepted
 * - _maximum (long long)_: greatest value to be accepted
 * - _step (long long)_: step size of the spinbox
 */
class PROPERTYGUIZEUG_API SignedIntegralEditor : public PropertyEditor
{
public:
    SignedIntegralEditor(reflectionzeug::SignedIntegralPropertyInterface * property, 
                         QWidget * parent = nullptr);

protected:
    LongLongSpinBox * m_spinBox;
    
    reflectionzeug::SignedIntegralPropertyInterface * m_property;
};

} // namespace propertyguizeug
