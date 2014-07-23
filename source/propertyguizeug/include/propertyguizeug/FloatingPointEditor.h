
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>

class QDoubleSpinBox;

namespace propertyguizeug
{

/** \brief Editor for floating point properties
 *
 * Supported options
 * - minimum (double): lowest value to be accepted
 * - maximum (double): greatest value to be accepted
 * - step (double): step size of the spinbox
 * - precision (uint): number of decimals used 
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
