
#include "ChoiceEditor.h"

#include <QHBoxLayout>
#include <QComboBox>

#include <propertyzeug/Property.h>

namespace zeug {
    
ChoiceEditor::ChoiceEditor(Property<std::string> * property, QWidget * parent)
:   QWidget(parent)
,   m_property(property)
{
    QStringList list;
    for (const std::string & choice : m_property->choices())
        list << QString::fromStdString(choice);
    
    QComboBox * comboBox = new QComboBox(this);
    comboBox->addItems(list);
    this->setFocusProxy(comboBox);
    comboBox->setCurrentText(QString::fromStdString(m_property->value()));
    
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->addWidget(comboBox);
    
    this->connect(comboBox, &QComboBox::currentTextChanged, this, &ChoiceEditor::setString);
}

ChoiceEditor::~ChoiceEditor()
{
}
    
void ChoiceEditor::setString(const QString & text)
{
    m_property->setValue(text.toStdString());
}

} // namespace
