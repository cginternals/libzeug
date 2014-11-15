#pragma once

#include <propertyguizeug/PropertyEditor.h>

namespace reflectionzeug
{
    class UnsignedIntegralPropertyInterface;
}

namespace propertyguizeug
{

/** \brief Editor for signed integral point properties
 *
 * Supported options
 * - minimum (unsigned long long): lowest value to be accepted
 * - maximum (unsigned long long): greatest value to be accepted
 * - step (unsigned long long): step size of the spinbox
 */
class PROPERTYGUIZEUG_API UnsignedIntegralEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::UnsignedIntegralPropertyInterface;
    
public:
    UnsignedIntegralEditor(reflectionzeug::UnsignedIntegralPropertyInterface * property, 
                           QWidget * parent = nullptr);

private:
    reflectionzeug::UnsignedIntegralPropertyInterface * m_property;
};

} // namespace propertyguizeug
