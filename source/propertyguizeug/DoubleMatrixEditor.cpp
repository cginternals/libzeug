
#include <propertyguizeug/DoubleMatrixEditor.h>

#include <propertyzeug/Property.h>

namespace propertyguizeug {
    
DoubleMatrixEditor::DoubleMatrixEditor(Property<std::vector<double>> * property, QWidget * parent)
:   MatrixEditor(property->fixedSize(), "(\\d+\\.?\\d*)", parent)
,   m_property(property)
{
    this->setText(QString::fromStdString(m_property->valueAsString()));
    this->connect(this, &QLineEdit::editingFinished, this, &DoubleMatrixEditor::setMatrix);
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

} // namespace
