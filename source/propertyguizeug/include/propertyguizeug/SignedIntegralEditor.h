#pragma once

#include <propertyguizeug/PropertyEditor.h>

#include <signalzeug/Connection.h>

namespace reflectionzeug
{
    class AbstractSignedIntegralInterface;
}

namespace propertyguizeug
{

/** \brief Editor for signed integral point properties
 *
 * Supported options
 * - minimum (long long): lowest value to be accepted
 * - maximum (long long): greatest value to be accepted
 * - step (long long): step size of the spinbox
 * - prefix (std::string): string shown before value
 * - suffix (std::string): string shown after value
 * - deferred (bool): defer changing the property's value until enter is pressed
 */
class PROPERTYGUIZEUG_API SignedIntegralEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::AbstractSignedIntegralInterface;
    
    static void paint(QPainter * painter, 
                      const QStyleOptionViewItem & option, 
                      reflectionzeug::AbstractSignedIntegralInterface & property);
    
public:
    SignedIntegralEditor(reflectionzeug::AbstractSignedIntegralInterface * property, 
                         QWidget * parent = nullptr);
    virtual ~SignedIntegralEditor();

private:    
    reflectionzeug::AbstractSignedIntegralInterface * m_property;
    signalzeug::Connection m_propertyChangedConnection;
};

} // namespace propertyguizeug
