#pragma once

#include <propertyguizeug/PropertyEditor.h>
#include <signalzeug/ScopedConnection.h>

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
 * - prefix (std::string): string shown before value
 * - suffix (std::string): string shown after value
 * - deferred (bool): defer changing the property's value until enter is pressed
 */
class PROPERTYGUIZEUG_API UnsignedIntegralEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::UnsignedIntegralPropertyInterface;
    
    static void paint(QPainter * painter, 
                      const QStyleOptionViewItem & option, 
                      reflectionzeug::UnsignedIntegralPropertyInterface & property);
    
public:
    UnsignedIntegralEditor(reflectionzeug::UnsignedIntegralPropertyInterface * property, 
                           QWidget * parent = nullptr);
    virtual ~UnsignedIntegralEditor();

private:
    reflectionzeug::UnsignedIntegralPropertyInterface * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
