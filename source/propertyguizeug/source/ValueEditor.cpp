
#include <QLineEdit>
#include <QHBoxLayout>

#include <reflectionzeug/AbstractValueProperty.h>

#include <propertyguizeug/ValueEditor.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
ValueEditor::ValueEditor(AbstractValueProperty * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_lineEdit(new QLineEdit(this))
,   m_property(property)
{   
    this->boxLayout()->addWidget(m_lineEdit);
    this->setFocusProxy(m_lineEdit);
    
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &ValueEditor::editingFinished);
}
    
void ValueEditor::editingFinished()
{
    m_property->fromString(m_lineEdit->text().toStdString());
}

} // namespace propertyguizeug
