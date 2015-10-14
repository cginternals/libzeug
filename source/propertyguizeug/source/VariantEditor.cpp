#include <propertyguizeug/VariantEditor.h>

#include <QComboBox>
#include <QLineEdit>

#include <reflectionzeug/property/Property.h>
#include <reflectionzeug/property/AbstractVariantInterface.h>

#include "util.h"

using namespace reflectionzeug;
namespace propertyguizeug
{
    
VariantEditor::VariantEditor(AbstractVariantInterface * property, QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{   
    QWidget * widget = createLineEdit();

    addWidget(widget);
    setFocusProxy(widget);
}

VariantEditor::~VariantEditor()
{
}

QWidget * VariantEditor::createLineEdit()
{
    auto lineEdit = new QLineEdit{this};
    
    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    lineEdit->setText(QString::fromStdString(prop->toString()));

    connect(lineEdit, &QLineEdit::textEdited, this, &VariantEditor::setString);
    
    m_propertyChangedConnection = prop->changed.connect(
        [this, lineEdit, prop]()
        {
            lineEdit->setText(QString::fromStdString(prop->toString()));
        });

    return lineEdit;
}

void VariantEditor::setString(const QString & text)
{
    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);
    prop->fromString(text.toStdString());
}

} // namespace propertyguizeug
