#include <propertyguizeug/StringEditor.h>

#include <QComboBox>
#include <QLineEdit>

#include <reflectionzeug/property/Property.h>

#include "util.h"

using namespace reflectionzeug;
namespace propertyguizeug
{
    
StringEditor::StringEditor(AbstractStringInterface * property, QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
,   m_model(nullptr)
{
    QWidget * widget = nullptr;

    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    assert(prop != nullptr);

    if (prop->hasOption("choices"))
        widget = createComboBox();
    else
        widget = createLineEdit();

    addWidget(widget);
    setFocusProxy(widget);
}

StringEditor::~StringEditor()
{
    delete m_model;
}

QWidget * StringEditor::createComboBox()
{
    auto comboBox = new QComboBox{this};

    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    assert(prop != nullptr);

    m_model = new ChoicesModel(prop);

    comboBox->setModel(m_model);
    comboBox->setCurrentText(QString::fromStdString(prop->toString()));

    if (m_model->hasIcons())
    {
        comboBox->setIconSize(m_model->iconSize());
    }
    
    using StringActivatedPtr = void (QComboBox::*) (const QString &);
    connect(comboBox, static_cast<StringActivatedPtr>(&QComboBox::activated),
            this, &StringEditor::setString);

    m_propertyChangedConnection = prop->changed.connect(
        [this, comboBox, prop]()
        {
            comboBox->setCurrentText(QString::fromStdString(prop->toString()));
        });

    return comboBox;
}

QWidget * StringEditor::createLineEdit()
{
    auto lineEdit = new QLineEdit{this};
    
    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    assert(prop != nullptr);

    lineEdit->setText(QString::fromStdString(prop->toString()));
    
    const auto deferred = prop->option<bool>("deferred", false);

    if (deferred)
    {
        connect(lineEdit, &QLineEdit::editingFinished,
            [this, lineEdit]
        {
            setString(lineEdit->text());
        });
    }
    else
    {
        connect(lineEdit, &QLineEdit::textEdited,
                this, &StringEditor::setString);
    }
    
    m_propertyChangedConnection = prop->changed.connect(
        [this, lineEdit, prop]()
        {
            lineEdit->setText(QString::fromStdString(prop->toString()));
        });

    return lineEdit;
}

void StringEditor::setString(const QString & text)
{
    AbstractProperty * prop = dynamic_cast<AbstractProperty *>(m_property);

    assert(prop != nullptr);

    prop->fromString(text.toStdString());
}

} // namespace propertyguizeug
