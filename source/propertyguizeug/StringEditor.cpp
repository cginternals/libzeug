
#include <propertyguizeug/StringEditor.h>

#include <propertyzeug/Property.h>

namespace zeug {
    
StringEditor::StringEditor(Property<std::string> * property, QWidget * parent)
:   QLineEdit(parent)
,   m_property(property)
{
    this->setText(QString::fromStdString(m_property->value()));
    this->connect(this, &QLineEdit::editingFinished, this, &StringEditor::setString);
}

StringEditor::~StringEditor()
{   
}
    
void StringEditor::setString()
{
    m_property->setValue(this->text().toStdString());
}

} // namespace
