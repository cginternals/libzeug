
#include <reflectionzeug/Property.h>

#include <propertyguizeug/StringEditor.h>
#include <propertyguizeug/ChoiceEditor.h>
#include <propertyguizeug/ColorEditor.h>
#include <propertyguizeug/FilePathEditor.h>
#include <propertyguizeug/DoubleEditor.h>
#include <propertyguizeug/EnumEditor.h>
#include <propertyguizeug/BoolEditor.h>
#include <propertyguizeug/ValueEditor.h>
#include <propertyguizeug/UnsignedIntegralEditor.h>
#include <propertyguizeug/SignedIntegralEditor.h>

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

QWidget * PropertyEditorFactory::createEditor(ValuePropertyInterface & property)
{
    property.accept(this);
    return m_editor;
}

QWidget * PropertyEditorFactory::createEditorWithParent(ValuePropertyInterface & property, QWidget * parent)
{
	QWidget * editor = createEditor(property);
	editor->setParent(parent);
	return editor;
}

void PropertyEditorFactory::visit(Property<bool> * property)
{
    m_editor = new BoolEditor(property);
}

void PropertyEditorFactory::visit(Property<double> * property)
{
    m_editor = new DoubleEditor(property);
}
    
void PropertyEditorFactory::visit(Property<std::string> * property)
{
    if (property->hasChoices())
        m_editor = new ChoiceEditor(property);
    else
        m_editor = new StringEditor(property);
}

void PropertyEditorFactory::visit(Property<Color> * property)
{
    m_editor = new ColorEditor(property);
}

void PropertyEditorFactory::visit(Property<FilePath> * property)
{
    m_editor = new FilePathEditor(property);
}

void PropertyEditorFactory::visit(reflectionzeug::ValuePropertyInterface * property)
{
    m_editor = new ValueEditor(property);
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

} // namespace propertyguizeug
