#pragma once

#include <QList>

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/propertyguizeug_api.h>

class QWidget;

namespace reflectionzeug
{
    class AbstractValueProperty;
}

namespace propertyguizeug
{

class AbstractPropertyEditorPlugin;
    
class PROPERTYGUIZEUG_API PropertyEditorFactory
{
public:
    PropertyEditorFactory();

    QWidget * createEditor(reflectionzeug::AbstractValueProperty & property);
    QWidget * createEditor(reflectionzeug::AbstractValueProperty & property, QWidget * parent);

    void addPlugin(AbstractPropertyEditorPlugin * plugin);
    
    void setEditor(QWidget * editor);

protected:
    QWidget * m_editor;

    QList<AbstractPropertyEditorPlugin *> m_plugins;
};

} // namespace propertyguizeug
