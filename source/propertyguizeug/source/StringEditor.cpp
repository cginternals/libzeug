#include <propertyguizeug/StringEditor.h>

#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>

#include <reflectionzeug/Property.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
StringEditor::StringEditor(StringPropertyInterface * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_property(property)
{   
    QWidget * widget;

    if (m_property->hasOption("choices"))
        widget = createComboBox();
    else
        widget = createLineEdit();

    this->boxLayout()->addWidget(widget);
    this->setFocusProxy(widget);
}

QWidget * StringEditor::createComboBox()
{
    QComboBox * comboBox = new QComboBox(this);

    std::vector<std::string> choices = m_property->option("choices").value<std::vector<std::string>>();
    
    QStringList items;
    for (const std::string & item : choices)
        items << QString::fromStdString(item);

    comboBox->addItems(items);
    comboBox->setCurrentText(QString::fromStdString(m_property->toString()));
    
    typedef void (QComboBox::*ActivatedPtr) (const QString &);
    connect(comboBox, (ActivatedPtr)(&QComboBox::activated),
            this, &StringEditor::setString);

    return comboBox;
}

QWidget * StringEditor::createLineEdit()
{
    QLineEdit * lineEdit = new QLineEdit(this);
    
    lineEdit->setText(QString::fromStdString(m_property->toString()));
    
    connect(lineEdit, &QLineEdit::textEdited,
            this, &StringEditor::setString);
    
    return lineEdit;
}

void StringEditor::setString(const QString & text)
{
    m_property->fromString(text.toStdString());
}

} // namespace propertyguizeug
