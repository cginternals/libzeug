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
,   m_model(nullptr)
{
    const auto strings = property->hasChoices() ? property->choicesStrings() : property->strings();

    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    assert(prop != nullptr);

    m_model = new ChoicesModel(prop, strings);

    auto comboBox = new QComboBox{this};

    comboBox->setModel(m_model);
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
    delete m_model;
}
    
void EnumEditor::setString(const QString & text)
{
    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    assert(prop != nullptr);

    prop->fromString(text.toStdString());
}

} // namespace propertyguizeug
