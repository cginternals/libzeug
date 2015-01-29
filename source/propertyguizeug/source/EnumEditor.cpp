#include <propertyguizeug/EnumEditor.h>

#include <QComboBox>

#include <reflectionzeug/EnumPropertyInterface.h>

#include "util.h"

using namespace reflectionzeug;
namespace propertyguizeug
{
    
EnumEditor::EnumEditor(
    reflectionzeug::EnumPropertyInterface * property, 
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

    m_propertyChangedConnection = m_property->valueChanged.connect(
        [this, comboBox]()
        {
            comboBox->setCurrentText(QString::fromStdString(m_property->toString()));
        });
}

EnumEditor::~EnumEditor()
{
    m_propertyChangedConnection.disconnect();
}
    
void EnumEditor::setString(const QString & text)
{
    m_property->fromString(text.toStdString());
}

} // namespace propertyguizeug
