
#include <QHBoxLayout>
#include <QComboBox>
#include <QVector>

#include <reflectionzeug/EnumPropertyInterface.h>

#include <propertyguizeug/EnumEditor.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
EnumEditor::EnumEditor(
    reflectionzeug::EnumPropertyInterface * property, 
    QWidget * parent)
:   PropertyEditor(parent)
,   m_property(property)
{
    QStringList list;

    std::vector<std::string> strings;
    if (property->hasChoices())
        strings = property->stringChoices();
    else
        strings = property->strings();

    for (const std::string & string : strings)
        list << QString::fromStdString(string);
    
    QComboBox * comboBox = new QComboBox(this);
    comboBox->addItems(list);
    this->setFocusProxy(comboBox);
    comboBox->setCurrentText(QString::fromStdString(m_property->toString()));
    
    this->boxLayout()->addWidget(comboBox);
    
    this->connect(comboBox, &QComboBox::currentTextChanged, this, &EnumEditor::setString);
}

EnumEditor::~EnumEditor()
{
}
    
void EnumEditor::setString(const QString & text)
{
    m_property->fromString(text.toStdString());
}

} // namespace propertyguizeug
