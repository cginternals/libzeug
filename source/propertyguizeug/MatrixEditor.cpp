
#include "MatrixEditor.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegularExpression>
#include <QTextStream>

namespace zeug {
    
MatrixEditor::MatrixEditor(int matrixSize, const QString & valueRegexString,
    const QString & initialText, QWidget * parent)
:   QWidget(parent)
,   m_lineEdit(new QLineEdit(this))
,   m_valueRegexString(valueRegexString)
,   m_matrixSize(matrixSize)
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->addWidget(m_lineEdit);
    
    this->setFocusProxy(m_lineEdit);
    m_lineEdit->setText(initialText);
    
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &MatrixEditor::parseString);
}

MatrixEditor::~MatrixEditor()
{   
}

QRegExp MatrixEditor::matrixRegex() const
{
    QString matrixRegexString;
    
    matrixRegexString += "\\s*\\(\\s*";
    for (int i = 0; i < m_matrixSize - 1; i++) {
        matrixRegexString += m_valueRegexString + "\\s*,\\s*";
    }
    matrixRegexString += m_valueRegexString + "\\s*\\)\\s*";

    QRegExp regExp(matrixRegexString);
    regExp.setCaseSensitivity(Qt::CaseInsensitive);
    return regExp;
}
    
void MatrixEditor::valuesFromText(const std::function<void(const QString &)> & functor) const
{
    QString text = m_lineEdit->text().replace(" ", "");

    QRegularExpression valueRegex(m_valueRegexString);
    QRegularExpressionMatchIterator matchIterator = valueRegex.globalMatch(text);

    while (matchIterator.hasNext()) {
        QString value = matchIterator.next().captured();
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
    return this->matrixRegex().exactMatch(m_lineEdit->text());
}

} // namespace
