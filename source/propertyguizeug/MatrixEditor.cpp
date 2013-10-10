
#include "MatrixEditor.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QRegularExpression>

namespace zeug {
    
MatrixEditor::MatrixEditor(int matrixSize, const QString & valueRegexString,
    const QString & initialText, QWidget * parent)
:   PropertyEditor(parent)
,   m_lineEdit(new QLineEdit(this))
,   m_valueRegexString(valueRegexString)
,   m_matrixSize(matrixSize)
{
    this->boxLayout()->addWidget(m_lineEdit);
    this->setFocusProxy(m_lineEdit);
    m_lineEdit->setText(initialText);
    
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &MatrixEditor::parseString);
}

MatrixEditor::~MatrixEditor()
{   
}

QRegularExpression MatrixEditor::matrixRegex() const
{
    QString matrixRegexString;
    
    matrixRegexString += "\\A\\s*\\(\\s*";
    for (int i = 0; i < m_matrixSize - 1; i++) {
        matrixRegexString += m_valueRegexString + "\\s*,\\s*";
    }
    matrixRegexString += m_valueRegexString + "\\s*\\)\\s*\\z";

    QRegularExpression regExp(matrixRegexString, QRegularExpression::CaseInsensitiveOption);
    return regExp;
}
    
void MatrixEditor::valuesFromText(const std::function<void(const QString &)> & functor) const
{
    QString text = m_lineEdit->text().replace(" ", "");

    QRegularExpression valueRegex(m_valueRegexString);
    QRegularExpressionMatchIterator matchIt = valueRegex.globalMatch(text);

    while (matchIt.hasNext()) {
        QString value = matchIt.next().captured();
        functor(value);
    }
}

void MatrixEditor::parseString()
{
    if (this->textMatchesRegex())
        this->setMatrix();
}

bool MatrixEditor::textMatchesRegex()
{
    QRegularExpressionMatch match = this->matrixRegex().match(m_lineEdit->text());
    return match.hasMatch();
}

} // namespace
