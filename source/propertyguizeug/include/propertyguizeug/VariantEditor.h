#pragma once

#include <reflectionzeug/property/property_declaration.h>

#include <signalzeug/ScopedConnection.h>

#include <propertyguizeug/PropertyEditor.h>

class QWidget;

namespace reflectionzeug
{
    class AbstractVariantInterface;
}

namespace propertyguizeug
{

/** \brief Editor for variants
 */
class PROPERTYGUIZEUG_API VariantEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::AbstractVariantInterface;
    
public:
    VariantEditor(reflectionzeug::AbstractVariantInterface * property, 
                 QWidget * parent = nullptr);
    virtual ~VariantEditor();

private:
    QWidget * createLineEdit();

    void setString(const QString & text);

private:    
    reflectionzeug::AbstractVariantInterface * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
