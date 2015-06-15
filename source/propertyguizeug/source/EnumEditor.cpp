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
    
    auto comboBox = new QComboBox{this};
    comboBox->addItems(util::toQStringList(strings));
    comboBox->setCurrentText(QString::fromStdString(m_property->toString()));
    
    addWidget(comboBox);
    setFocusProxy(comboBox);
    
    connect(comboBox, &QComboBox::currentTextChanged, 
            this, &EnumEditor::setString);

    m_propertyChangedConnection = dynamic_cast<AbstractProperty *>(m_property)->changed.connect(
        [this, comboBox]()
        {
            comboBox->setCurrentText(QString::fromStdString(m_property->toString()));
        });
}

EnumEditor::~EnumEditor()
{
}
    
void EnumEditor::setString(const QString & text)
{
    m_property->fromString(text.toStdString());
}

} // namespace propertyguizeug
