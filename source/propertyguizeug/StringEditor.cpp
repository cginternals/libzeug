
#include <propertyguizeug/StringEditor.h>

namespace propertyguizeug {
    
StringEditor::StringEditor(Property<std::string> * property, QWidget * parent)
:   QLineEdit(parent)
,   m_property(property)
{
    this->setText(QString::fromStdString(m_property->value()));
    this->connect(this, (&QLineEdit::textChanged),
                  [this](const QString & text) {
                      m_property->setValue(text.toStdString());
                  });
}

StringEditor::~StringEditor()
{   
}

} // namespace
