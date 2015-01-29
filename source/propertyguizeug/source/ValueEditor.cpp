#include <propertyguizeug/ValueEditor.h>

#include <QLineEdit>

#include <reflectionzeug/AbstractValueProperty.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
ValueEditor::ValueEditor(AbstractValueProperty * property, QWidget * parent)
:   PropertyEditor{parent}
,   m_lineEdit{new QLineEdit{this}}
,   m_property{property}
{   
    addWidget(m_lineEdit);
    setFocusProxy(m_lineEdit);
    
    m_lineEdit->setText(QString::fromStdString(m_property->toString()));
    
    connect(m_lineEdit, &QLineEdit::editingFinished, 
            this, &ValueEditor::editingFinished);

    m_propertyChangedConnection = m_property->valueChanged.connect(
        [this]()
        {
            m_lineEdit->setText(QString::fromStdString(m_property->toString()));
        });
}

ValueEditor::~ValueEditor()
{
    m_propertyChangedConnection.disconnect();
}
    
void ValueEditor::editingFinished()
{
    m_property->fromString(m_lineEdit->text().toStdString());
}

} // namespace propertyguizeug
