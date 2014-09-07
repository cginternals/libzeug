
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

#include <propertyguizeug/PropertyEditorFactory.h>


using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyEditorFactory::PropertyEditorFactory()
:   m_editor(nullptr)
{
}

PropertyEditorFactory::~PropertyEditorFactory()
{
}

QWidget * PropertyEditorFactory::createEditor(AbstractValueProperty & property)
{
    property.accept(this);
    return m_editor;
}

QWidget * PropertyEditorFactory::createEditorWithParent(AbstractValueProperty & property, QWidget * parent)
{
	QWidget * editor = createEditor(property);
	editor->setParent(parent);
	return editor;
}

void PropertyEditorFactory::visit(Property<bool> * property)
{
    m_editor = new BoolEditor(property);
}

void PropertyEditorFactory::visit(Property<FilePath> * property)
{
    m_editor = new FilePathEditor(property);
}

void PropertyEditorFactory::visit(reflectionzeug::AbstractValueProperty * property)
{
    m_editor = new ValueEditor(property);
}
    
void PropertyEditorFactory::visit(reflectionzeug::ColorPropertyInterface * property)
{
    m_editor = new ColorEditor(property);
}

void PropertyEditorFactory::visit(reflectionzeug::EnumPropertyInterface * property)
{
    m_editor = new EnumEditor(property);
}

void PropertyEditorFactory::visit(reflectionzeug::UnsignedIntegralPropertyInterface * property)
{
    m_editor = new UnsignedIntegralEditor(property);
}

void PropertyEditorFactory::visit(reflectionzeug::SignedIntegralPropertyInterface * property)
{
    m_editor = new SignedIntegralEditor(property);
}

void PropertyEditorFactory::visit(reflectionzeug::FloatingPointPropertyInterface * property)
{
    m_editor = new FloatingPointEditor(property);
}

void PropertyEditorFactory::visit(reflectionzeug::StringPropertyInterface * property)
{
    m_editor = new StringEditor(property);
}

} // namespace propertyguizeug
