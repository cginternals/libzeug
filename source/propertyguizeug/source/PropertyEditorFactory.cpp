#include <propertyguizeug/PropertyEditorFactory.h>

#include <cassert>

#include <reflectionzeug/property/Property.h>

#include <propertyguizeug/BoolEditor.h>
#include <propertyguizeug/ColorEditor.h>
#include <propertyguizeug/EnumEditor.h>
#include <propertyguizeug/FilePathEditor.h>
#include <propertyguizeug/FloatingPointEditor.h>
#include <propertyguizeug/SignedIntegralEditor.h>
#include <propertyguizeug/StringEditor.h>
#include <propertyguizeug/UnsignedIntegralEditor.h>
#include <propertyguizeug/ValueEditor.h>


#include <propertyguizeug/PropertyEditorPlugin.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyEditorFactory::PropertyEditorFactory()
: m_editor{nullptr}
, m_parentWidget{nullptr}
{
    addPlugin(new PropertyEditorPlugin<
        BoolEditor,
        ColorEditor,
        EnumEditor,
        FilePathEditor,
        FloatingPointEditor,
        SignedIntegralEditor,
        StringEditor,
        UnsignedIntegralEditor>{});
}

QWidget * PropertyEditorFactory::createEditor(
    AbstractProperty & property, 
    QWidget * parent)
{
    assert(parent);

    m_editor = nullptr;
    m_parentWidget = parent;

    for (auto plugin : m_plugins)
    {
        property.accept(plugin);

        if (m_editor)
            break;
    }

    // [TODO] Fallback to default editor
    /*
    if (!m_editor)
        m_editor = new ValueEditor{&property, m_parentWidget};
    */

    return m_editor;
}

void PropertyEditorFactory::addPlugin(AbstractPropertyEditorPlugin * plugin)
{
    assert(plugin);
    plugin->setFactory(this);
    m_plugins.prepend(plugin);
}

void PropertyEditorFactory::setEditor(QWidget * editor)
{
    m_editor = editor;
}

QWidget * PropertyEditorFactory::parentWidget() const
{
    return m_parentWidget;
}

} // namespace propertyguizeug
