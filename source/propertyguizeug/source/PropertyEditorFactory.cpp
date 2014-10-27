#include <propertyguizeug/PropertyEditorFactory.h>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/StringEditor.h>
#include <propertyguizeug/ColorEditor.h>
#include <propertyguizeug/FilePathEditor.h>
#include <propertyguizeug/EnumEditor.h>
#include <propertyguizeug/BoolEditor.h>
#include <propertyguizeug/ValueEditor.h>
#include <propertyguizeug/UnsignedIntegralEditor.h>
#include <propertyguizeug/SignedIntegralEditor.h>
#include <propertyguizeug/FloatingPointEditor.h>

#include <propertyguizeug/AbstractPropertyEditorPlugin.h>
#include <propertyguizeug/PropertyEditorPlugin.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyEditorFactory::PropertyEditorFactory()
:   m_editor(nullptr)
{
    addPlugin(new PropertyEditorPlugin<
        StringEditor, 
        ColorEditor, 
        FilePathEditor, 
        EnumEditor, 
        BoolEditor, 
        UnsignedIntegralEditor, 
        SignedIntegralEditor, 
        FloatingPointEditor>());
}

PropertyEditorFactory::~PropertyEditorFactory()
{
    qDeleteAll(m_plugins);
}

QWidget * PropertyEditorFactory::createEditor(AbstractValueProperty & property)
{
    m_editor = nullptr;

    for (AbstractPropertyEditorPlugin * plugin : m_plugins)
    {
        property.accept(plugin);

        if (m_editor)
            return m_editor;
    }
    
    return new ValueEditor(&property);
}

QWidget * PropertyEditorFactory::createEditor(AbstractValueProperty & property, QWidget * parent)
{
	QWidget * editor = createEditor(property);
	editor->setParent(parent);
	return editor;
}

void PropertyEditorFactory::addPlugin(AbstractPropertyEditorPlugin * plugin)
{
    if (plugin == nullptr)
        return;

    plugin->setFactory(this);
    m_plugins.prepend(plugin);
}

void PropertyEditorFactory::setEditor(QWidget * editor)
{
    m_editor = editor;
}

} // namespace propertyguizeug
