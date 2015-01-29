#pragma once

#include <reflectionzeug/property_declaration.h>
#include <signalzeug/Connection.h>

#include <propertyguizeug/PropertyEditor.h>

namespace reflectionzeug
{
    class FloatingPointPropertyInterface;
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
 */
class PROPERTYGUIZEUG_API FloatingPointEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::FloatingPointPropertyInterface;
    
    static void paint(QPainter * painter, 
                      const QStyleOptionViewItem & option, 
                      reflectionzeug::FloatingPointPropertyInterface & property);
    
public:
    FloatingPointEditor(reflectionzeug::FloatingPointPropertyInterface * property, 
                        QWidget * parent = nullptr);
    virtual ~FloatingPointEditor();
                        
private:
    static const int s_defaultPrecision;

private:
    reflectionzeug::FloatingPointPropertyInterface * m_property;
    signalzeug::Connection m_propertyChangedConnection;
};

} // namespace propertyguizeug
