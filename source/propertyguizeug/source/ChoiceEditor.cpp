
#include <QHBoxLayout>
#include <QComboBox>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/ChoiceEditor.h>

using namespace reflectionzeug;
namespace propertyguizeug
{

ChoiceEditor::ChoiceEditor(StringPropertyInterface * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_property(property)
,   m_comboBox(nullptr)
{
    QStringList list;
    for (const std::string & choice : m_property->choices())
        list << QString::fromStdString(choice);

    m_comboBox = new QComboBox(this);
    m_comboBox->addItems(list);
    this->setFocusProxy(m_comboBox);
    m_comboBox->setCurrentText(QString::fromStdString(m_property->toString()));

    this->boxLayout()->addWidget(m_comboBox);

    this->connect(m_comboBox, &QComboBox::currentTextChanged, this, &ChoiceEditor::setString);

    property->choicesChanged.connect(this, &ChoiceEditor::propertyChoicesChanged);
}

ChoiceEditor::~ChoiceEditor()
{
}

void ChoiceEditor::setString(const QString & text)
{
    m_property->fromString(text.toStdString());
}

void ChoiceEditor::propertyChoicesChanged(const std::vector<std::string> & choices)
{
    // Block signals from the combo box, while we are changing its values
    bool blockedState = m_comboBox->blockSignals(true);

    // Remember selected value
    QString oldValue = m_comboBox->currentText();

    // Update list of choices
    QStringList list;
    for (const std::string & choice : m_property->choices())
        list << QString::fromStdString(choice);

    // Set new list
    m_comboBox->clear();
    m_comboBox->addItems(list);

    // Try to maintain the selected value
    bool selected = false;
    if (list.contains(oldValue)) {
        m_comboBox->setCurrentText(oldValue);
        selected = true;
    }

    // Re-enable signals
    m_comboBox->blockSignals(blockedState);

    // If the old text is not available any more, select the first item
    m_comboBox->setCurrentIndex(0);
}

} // namespace propertyguizeug
