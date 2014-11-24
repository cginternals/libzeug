#pragma once

#include <propertyguizeug/PropertyBrowser.h>

#include <propertyguizeug/PropertyEditorPlugin.h>
#include <propertyguizeug/PropertyPainterPlugin.h>

namespace propertyguizeug
{

template <typename... Editors>
void PropertyBrowser::addEditorPlugin()
{
    addEditorPlugin(new PropertyEditorPlugin<Editors...>{});
}

template <typename... Editors>
void PropertyBrowser::addPainterPlugin()
{
    addPainterPlugin(new PropertyPainterPlugin<Editors...>{});
}

} // namespace propertyguizeug
