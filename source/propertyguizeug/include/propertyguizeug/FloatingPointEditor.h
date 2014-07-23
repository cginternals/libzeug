
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>

class QDoubleSpinBox;

namespace propertyguizeug
{

/** \brief Editor for floating point propertyies
 *
 * Supported options
 * - _minimum (double)_: lowest value to be accepted
 * - _maximum (double)_: greatest value to be accepted
 * - _step (double)_: step size of the spinbox
 * - _precision (uint)_: number of decimals used 
 */
class PROPERTYGUIZEUG_API FloatingPointEditor : public PropertyEditor
{
public:
    FloatingPointEditor(reflectionzeug::FloatingPointPropertyInterface * property, QWidget * parent = nullptr);

protected:
    QDoubleSpinBox * m_spinBox;
    
    reflectionzeug::FloatingPointPropertyInterface * m_property;
};

} // namespace propertyguizeug
