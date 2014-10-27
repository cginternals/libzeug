#pragma once

#include <reflectionzeug/PropertyVisitor.h>

#include <propertyguizeug/AbstractPropertyEditorPlugin.h>

namespace propertyguizeug
{

template <typename Editor, typename... MoreEditors>
class PropertyEditorPlugin : 
    public PropertyEditorPlugin<Editor>, 
    public PropertyEditorPlugin<MoreEditors...>
{
};

template <typename Editor>
class PropertyEditorPlugin<Editor> : 
    public reflectionzeug::PropertyVisitor<typename Editor::PropertyType>,
    public virtual AbstractPropertyEditorPlugin
{
public:
    using PropertyType = typename Editor::PropertyType;

public:
    virtual void visit(PropertyType * property)
    {
        setEditor(new Editor(property));
    }
};

} // namespace propertyguizeug
