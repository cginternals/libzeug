#pragma once

#include <QList>

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
    virtual ~PropertyEditorFactory();

    QWidget * createEditor(reflectionzeug::AbstractValueProperty & property);
    QWidget * createEditor(reflectionzeug::AbstractValueProperty & property, QWidget * parent);

    void addPlugin(AbstractPropertyEditorPlugin * plugin);

    void setEditor(QWidget * editor);

private:
    QList<AbstractPropertyEditorPlugin *> m_plugins;
    QWidget * m_editor;
};

} // namespace propertyguizeug
