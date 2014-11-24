#pragma once

#include <reflectionzeug/PropertyVisitor.h>

#include <propertyguizeug/PropertyEditorFactory.h>

namespace propertyguizeug
{

class AbstractPropertyEditorPlugin : public virtual reflectionzeug::AbstractPropertyVisitor
{
public:
    virtual ~AbstractPropertyEditorPlugin() = default;

    void setFactory(PropertyEditorFactory * factory) { m_factory = factory; }

protected:
    PropertyEditorFactory * factory() const { return m_factory; }

private:
    PropertyEditorFactory * m_factory;
};

template <typename Editor, typename... MoreEditors>
class PropertyEditorPlugin : 
    public PropertyEditorPlugin<Editor>, 
    public PropertyEditorPlugin<MoreEditors...>
{
};

template <typename Editor>
class PropertyEditorPlugin<Editor> : 
    public reflectionzeug::PropertyVisitor<typename Editor::Type>,
    public virtual AbstractPropertyEditorPlugin
{
public:
    virtual void visit(typename Editor::Type * property)
    {
        this->factory()->setEditor(new Editor(property));
    }
};

} // namespace propertyguizeug
