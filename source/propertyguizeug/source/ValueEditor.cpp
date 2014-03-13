
#include <QLineEdit>
#include <QHBoxLayout>

#include <reflectionzeug/ValuePropertyInterface.h>

#include "ValueEditor.h"

using namespace reflectionzeug;
namespace propertyguizeug
{
    
ValueEditor::ValueEditor(ValuePropertyInterface * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_lineEdit(new QLineEdit(this))
,   m_property(property)
{   
    this->boxLayout()->addWidget(m_lineEdit);
    this->setFocusProxy(m_lineEdit);
    
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
    this->connect(m_lineEdit, &QLineEdit::editingFinished, this, &ValueEditor::editingFinished);
}

ValueEditor::~ValueEditor()
{   
}
    
void ValueEditor::editingFinished()
{
    m_property->fromString(m_lineEdit->text().toStdString());
}

} // namespace propertyguizeug
