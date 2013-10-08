
#include <propertyguizeug/PropertyEditorFactory.h>

#include <propertyzeug/Property.h>

#include <propertyguizeug/VectorEditor.h>

#include "IntegerEditor.h"
#include "StringEditor.h"
#include "ChoiceEditor.h"
#include "ColorEditor.h"
#include "FilePathEditor.h"
#include "DoubleEditor.h"
#include "BoolEditor.h"
#include "BoolMatrixEditor.h"
#include "IntMatrixEditor.h"
#include "DoubleMatrixEditor.h"

namespace zeug {
    
PropertyEditorFactory::PropertyEditorFactory()
:   m_editor(nullptr)
{
}

PropertyEditorFactory::~PropertyEditorFactory()
{
}

QWidget * PropertyEditorFactory::createEditor(ValueProperty & property)
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
  
} // namespace
