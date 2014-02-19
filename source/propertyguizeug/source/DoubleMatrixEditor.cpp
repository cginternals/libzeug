
#include <QLineEdit>

#include <reflectionzeug/Property.h>

#include "DoubleMatrixEditor.h"

using namespace reflectionzeug;
namespace propertyguizeug
{
    
DoubleMatrixEditor::DoubleMatrixEditor(Property<std::vector<double>> * property, QWidget * parent)
:   MatrixEditor(property->fixedSize(),
                 "(-?\\d+\\.?\\d*)",
                 QString::fromStdString(property->valueAsString()),
                 parent)
,   m_property(property)
{
}

DoubleMatrixEditor::~DoubleMatrixEditor()
{   
}
    
void DoubleMatrixEditor::setMatrix()
{
    std::vector<double> matrix;
    this->valuesFromText([&matrix] (const QString & value) {
        matrix.push_back(value.toDouble());
    });
    m_property->setValue(matrix);
}

} // namespace propertyguizeug
