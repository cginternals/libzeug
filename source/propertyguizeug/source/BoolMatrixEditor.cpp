
#include <QLineEdit>
#include <reflectionzeug/Property.h>

#include "BoolMatrixEditor.h"

using namespace reflectionzeug;
namespace propertyguizeug
{
    
BoolMatrixEditor::BoolMatrixEditor(Property<std::vector<bool>> * property, QWidget * parent)
:   MatrixEditor(property->fixedSize(),
                 this->valueRegexString(),
                 QString::fromStdString(property->valueAsString()),
                 parent)
,   m_property(property)
{
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
    
QString BoolMatrixEditor::valueRegexString() const
{
    return "(" + this->trueValues().join("|") + "|" + this->falseValues().join("|") + ")";
}
    
QStringList BoolMatrixEditor::trueValues() const
{
    return QStringList() << "true" << "1" << "yes" << "on" << "t";
}

QStringList BoolMatrixEditor::falseValues() const
{
    return QStringList() << "false" << "0" << "no" << "off" << "f";
}

} // namespace propertyguizeug
