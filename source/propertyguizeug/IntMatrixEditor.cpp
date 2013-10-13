
#include "IntMatrixEditor.h"

#include <QLineEdit>
#include <propertyzeug/Property.h>

namespace zeug {
    
IntMatrixEditor::IntMatrixEditor(Property<std::vector<int>> * property, QWidget * parent)
:   MatrixEditor(property->fixedSize(),
                 "(-?\\d+)",
                 QString::fromStdString(property->valueAsString()),
                 parent)
,   m_property(property)
{
}

IntMatrixEditor::~IntMatrixEditor()
{   
}
    
void IntMatrixEditor::setMatrix()
{
    std::vector<int> matrix;
    this->valuesFromText([&matrix] (const QString & value) {
        matrix.push_back(value.toInt());
    });
    m_property->setValue(matrix);
}

} // namespace
