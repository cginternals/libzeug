
#include "StringEditor.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <propertyzeug/Property.h>

namespace zeug {
    
StringEditor::StringEditor(Property<std::string> * property, QWidget * parent)
:   QWidget(parent)
,   m_lineEdit(new QLineEdit(this))
,   m_property(property)
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->setSpacing(3);
    
    layout->addWidget(m_lineEdit);

    this->setFocusProxy(m_lineEdit);
    
    m_lineEdit->setText(QString::fromStdString(m_property->value()));
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &StringEditor::editingFinished);
}

StringEditor::~StringEditor()
{   
}
    
void StringEditor::editingFinished()
{
    m_property->setValue(m_lineEdit->text().toStdString());
}

} // namespace
