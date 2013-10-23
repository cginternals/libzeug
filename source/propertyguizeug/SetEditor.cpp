
#include "SetEditor.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QRegularExpression>

namespace zeug {
    
SetEditor::SetEditor(const QString & valueRegexString,
    const QString & initialText, QWidget * parent)
:   PropertyEditor(parent)
,   m_lineEdit(new QLineEdit(this))
,   m_valueRegexString(valueRegexString)
{
    this->boxLayout()->addWidget(m_lineEdit);
    this->setFocusProxy(m_lineEdit);
    m_lineEdit->setText(initialText);
    
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &SetEditor::parseString);
}

SetEditor::~SetEditor()
{
}

QRegularExpression SetEditor::setRegex() const
{
    return QRegularExpression(
	QString("\\A\\s*(\\s*(%1|%1\\s*(,\\s*%1)*\\s*)\\s*\\z").arg(m_valueRegexString),
	QRegularExpression::CaseInsensitiveOption
    );
}
    
void SetEditor::valuesFromText(const std::function<void(const QString &)> & functor) const
{
    QString text = m_lineEdit->text().replace(" ", "");

    QRegularExpression valueRegex(m_valueRegexString);
    QRegularExpressionMatchIterator matchIt = valueRegex.globalMatch(text);

    while (matchIt.hasNext()) {
        functor(matchIt.next().captured());
    }
}

void SetEditor::parseString()
{
    if (this->textMatchesRegex())
        this->setSet();
}

bool SetEditor::textMatchesRegex()
{
    QRegularExpressionMatch match = this->setRegex().match(m_lineEdit->text());
    return match.hasMatch();
}

} // namespace
