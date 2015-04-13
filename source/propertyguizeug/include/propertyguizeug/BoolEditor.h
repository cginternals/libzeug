#pragma once

#include <reflectionzeug/property_declaration.h>
#include <signalzeug/ScopedConnection.h>

#include <propertyguizeug/propertyguizeug_api.h>
#include <propertyguizeug/PropertyEditor.h>

class QPainter;
class QStyleOptionViewItem;

namespace propertyguizeug
{
    
class PROPERTYGUIZEUG_API BoolEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::Property<bool>;

    static void paint(QPainter * painter, 
                      const QStyleOptionViewItem & option, 
                      reflectionzeug::Property<bool> & property);

public:
    BoolEditor(reflectionzeug::Property<bool> * property, 
               QWidget * parent = nullptr);
    virtual ~BoolEditor();

private:
    reflectionzeug::Property<bool> * m_property;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
