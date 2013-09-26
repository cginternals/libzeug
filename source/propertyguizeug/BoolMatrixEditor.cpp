
#include <propertyguizeug/BoolMatrixEditor.h>

namespace propertyguizeug {
    
BoolMatrixEditor::BoolMatrixEditor(Property<std::vector<bool>> * property, QWidget * parent)
:   MatrixEditor(property->fixedSize(),
                 "(" + this->trueValues().join("|") + "|" + this->falseValues().join("|") + ")",
                 parent)
,   m_property(property)
{
    this->setText(QString::fromStdString(m_property->valueAsString()));
    this->connect(this, &QLineEdit::editingFinished, this, &BoolMatrixEditor::setMatrix);
}

BoolMatrixEditor::~BoolMatrixEditor()
{   
}
    
void BoolMatrixEditor::setMatrix()
{
    std::vector<bool> matrix;
    this->valuesFromText([this, &matrix] (const QString & value) {
        matrix.push_back(this->stringToBool(value));
    });
    m_property->setValue(matrix);
}
    
bool BoolMatrixEditor::stringToBool(const QString & string) const
{
    return this->trueValues().contains(string, Qt::CaseInsensitive);
}
    
QStringList BoolMatrixEditor::trueValues() const
{
    return {"true", "1", "yes", "on", "t"};
}

QStringList BoolMatrixEditor::falseValues() const
{
    return {"false", "0", "no", "off", "f"};
}

} // namespace
