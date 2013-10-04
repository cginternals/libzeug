
#include <propertyguizeug/MatrixEditor.h>

#include <QRegExpValidator>
#include <QRegularExpression>
#include <QTextStream>

namespace zeug {
    
MatrixEditor::MatrixEditor(int matrixSize, const QString & valueRegexString,
    QWidget * parent)
:   QLineEdit(parent)
,   m_valueRegexString(valueRegexString)
{
    QRegExpValidator * validator = new QRegExpValidator(this->matrixRegex(matrixSize, m_valueRegexString), this);
    this->setValidator(validator);
}

MatrixEditor::~MatrixEditor()
{   
}

QRegExp MatrixEditor::matrixRegex(int matrixSize, const QString & valueRegexString) const
{
    QString matrixRegexString;
    
    matrixRegexString += "\\s*\\(\\s*";
    for (int i = 0; i < matrixSize - 1; i++) {
        matrixRegexString += valueRegexString + "\\s*,\\s*";
    }
    matrixRegexString += valueRegexString + "\\s*\\)\\s*";

    QRegExp regExp(matrixRegexString);
    regExp.setCaseSensitivity(Qt::CaseInsensitive);
    return regExp;
}
    
void MatrixEditor::valuesFromText(const std::function<void(const QString &)> & functor) const
{
    QString text = this->text().replace(" ", "");

    QRegularExpression valueRegex(m_valueRegexString);
    QRegularExpressionMatchIterator matchIterator = valueRegex.globalMatch(text);

    while (matchIterator.hasNext()) {
        QString value = matchIterator.next().captured();
        functor(value);
    }
}

} // namespace
