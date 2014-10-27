#include <propertyguizeug/AbstractPropertyEditorPlugin.h>

#include <cassert>

#include <propertyguizeug/PropertyEditorFactory.h>


namespace propertyguizeug
{

AbstractPropertyEditorPlugin::AbstractPropertyEditorPlugin()
:   m_factory(nullptr)
{ 
}

void AbstractPropertyEditorPlugin::setFactory(PropertyEditorFactory * factory)
{
    m_factory = factory;
}

void AbstractPropertyEditorPlugin::setEditor(QWidget * editor)
{
    assert(m_factory);
    m_factory->setEditor(editor);
}

} // namespace propertyguizeug
