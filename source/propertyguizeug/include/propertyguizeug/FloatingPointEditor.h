#pragma once

#include <reflectionzeug/property/property_declaration.h>

#include <signalzeug/ScopedConnection.h>

#include <propertyguizeug/PropertyEditor.h>

namespace reflectionzeug
{
    class AbstractFloatingPointInterface;
}

namespace propertyguizeug
{

/** \brief Editor for floating point properties
 *
 * Supported options
 * - minimum (double): lowest value to be accepted
 * - maximum (double): greatest value to be accepted
 * - step (double): step size of the spinbox
 * - precision (uint): number of decimals used
 * - prefix (std::string): string shown before value
 * - suffix (std::string): string shown after value 
 * - deferred (bool): defer changing the property's value until enter is pressed
 */
class PROPERTYGUIZEUG_API FloatingPointEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::AbstractFloatingPointInterface;
    
    static void paint(QPainter * painter, 
                      const QStyleOptionViewItem & option, 
                      reflectionzeug::AbstractFloatingPointInterface & property);
    
public:
    FloatingPointEditor(reflectionzeug::AbstractFloatingPointInterface * property, 
                        QWidget * parent = nullptr);
    virtual ~FloatingPointEditor();
                        
private:
    static const int s_defaultPrecision;

private:
    reflectionzeug::AbstractFloatingPointInterface * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
