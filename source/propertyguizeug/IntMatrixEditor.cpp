
#include <propertyguizeug/IntMatrixEditor.h>

#include <propertyzeug/Property.h>

namespace zeug {
    
IntMatrixEditor::IntMatrixEditor(Property<std::vector<int>> * property, QWidget * parent)
:   MatrixEditor(property->fixedSize(), "(\\d+)", parent)
,   m_property(property)
{
    this->setText(QString::fromStdString(m_property->valueAsString()));
    this->connect(this, &QLineEdit::editingFinished, this, &IntMatrixEditor::setMatrix);
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
