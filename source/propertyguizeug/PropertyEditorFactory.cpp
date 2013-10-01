
#include <propertyguizeug/PropertyEditorFactory.h>

#include <propertyzeug/Property.h>

#include <propertyguizeug/IntegerEditor.h>
#include <propertyguizeug/StringEditor.h>
#include <propertyguizeug/ChoiceEditor.h>
#include <propertyguizeug/VectorEditor.h>
#include <propertyguizeug/ColorEditor.h>
#include <propertyguizeug/FilePathEditor.h>
#include <propertyguizeug/DoubleEditor.h>
#include <propertyguizeug/BoolEditor.h>
#include <propertyguizeug/BoolMatrixEditor.h>
#include <propertyguizeug/IntMatrixEditor.h>
#include <propertyguizeug/DoubleMatrixEditor.h>


namespace propertyguizeug {
    
PropertyEditorFactory::PropertyEditorFactory()
:   m_editor(nullptr)
{
}

PropertyEditorFactory::~PropertyEditorFactory()
{
}

QWidget * PropertyEditorFactory::createEditor(AbstractProperty & property)
{
    property.accept(*this);
    return m_editor;
}

void PropertyEditorFactory::visit(Property<bool> & property)
{
    m_editor = new BoolEditor(&property);
}
    
void PropertyEditorFactory::visit(Property<int> & property)
{
    m_editor = new IntegerEditor(&property);
}
    
void PropertyEditorFactory::visit(Property<double> & property)
{
    m_editor = new DoubleEditor(&property);
}
    
void PropertyEditorFactory::visit(Property<std::string> & property)
{
    if (property.hasChoices())
        m_editor = new ChoiceEditor(&property);
    else
        m_editor = new StringEditor(&property);
}

void PropertyEditorFactory::visit(Property<Color> & property)
{
    m_editor = new ColorEditor(&property);
}

void PropertyEditorFactory::visit(Property<FilePath> & property)
{
    m_editor = new FilePathEditor(&property);
}

void PropertyEditorFactory::visit(Property<std::vector<bool>> & property)
{
    if (property.rows() > 1)
        m_editor = new BoolMatrixEditor(&property);
    // TODO add BoolVectorEditor
}

void PropertyEditorFactory::visit(Property<std::vector<int>> & property)
{
    if (property.rows() > 1)
        m_editor = new IntMatrixEditor(&property);
    else
        m_editor = new VectorEditor<int>(&property);
}

void PropertyEditorFactory::visit(Property<std::vector<double>> & property)
{
    if (property.rows() > 1)
        m_editor = new DoubleMatrixEditor(&property);
    
    // TODO add DoubleVectorEditor
}

void PropertyEditorFactory::visit(PropertyGroup & property)
{
    // should not be called
}
    
} // namespace
