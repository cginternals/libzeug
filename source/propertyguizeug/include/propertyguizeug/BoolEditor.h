#pragma once

#include <reflectionzeug/property_declaration.h>

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

private:
    reflectionzeug::Property<bool> * m_property;
};

} // namespace propertyguizeug
