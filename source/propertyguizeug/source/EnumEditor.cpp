#include <propertyguizeug/EnumEditor.h>

#include <QComboBox>

#include <reflectionzeug/property/AbstractProperty.h>
#include <reflectionzeug/property/AbstractEnumInterface.h>

#include "util.h"

using namespace reflectionzeug;
namespace propertyguizeug
{
    
EnumEditor::EnumEditor(
    reflectionzeug::AbstractEnumInterface * property, 
    QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{
    auto strings = std::vector<std::string>{};
    if (property->hasChoices())
        strings = property->choicesStrings();
    else
        strings = property->strings();

    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    auto comboBox = new QComboBox{this};
    comboBox->addItems(util::toQStringList(strings));
    comboBox->setCurrentText(QString::fromStdString(prop->toString()));
    
    addWidget(comboBox);
    setFocusProxy(comboBox);
    
    connect(comboBox, &QComboBox::currentTextChanged, 
            this, &EnumEditor::setString);

    m_propertyChangedConnection = prop->changed.connect(
        [this, prop, comboBox]()
        {
            comboBox->setCurrentText(QString::fromStdString(prop->toString()));
        });
}

EnumEditor::~EnumEditor()
{
}
    
void EnumEditor::setString(const QString & text)
{
    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    prop->fromString(text.toStdString());
}

} // namespace propertyguizeug
