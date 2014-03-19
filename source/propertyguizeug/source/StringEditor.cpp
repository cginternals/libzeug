
#include <QLineEdit>
#include <QHBoxLayout>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/StringEditor.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
StringEditor::StringEditor(Property<std::string> * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_lineEdit(new QLineEdit(this))
,   m_property(property)
{   
    this->boxLayout()->addWidget(m_lineEdit);
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

} // namespace propertyguizeug
