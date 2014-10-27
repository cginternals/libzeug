#pragma once

#include <reflectionzeug/AbstractPropertyVisitor.h>

#include <propertyguizeug/propertyguizeug_api.h>

class QWidget;

namespace propertyguizeug
{

class PropertyEditorFactory;

class PROPERTYGUIZEUG_API AbstractPropertyEditorPlugin : public virtual reflectionzeug::AbstractPropertyVisitor
{
public:
    AbstractPropertyEditorPlugin();

    void setFactory(PropertyEditorFactory * factory);

protected:
    void setEditor(QWidget * editor);

private:
    PropertyEditorFactory * m_factory;
};

} // namespace propertyguizeug
