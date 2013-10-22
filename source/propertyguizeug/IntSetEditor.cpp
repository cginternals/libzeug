
#include "IntSetEditor.h"

#include <QLineEdit>
#include <propertyzeug/Property.h>

namespace zeug {
    
IntSetEditor::IntSetEditor(Property<std::set<int>> * property, QWidget * parent)
:   SetEditor("(-?\\d+)",
                 QString::fromStdString(property->valueAsString()),
                 parent)
,   m_property(property)
{
}

IntSetEditor::~IntSetEditor()
{   
}
    
void IntSetEditor::setSet()
{
    std::set<int> set;
    this->valuesFromText([&set] (const QString & value) {
        set.insert(value.toInt());
    });
    m_property->setValue(set);
}

} // namespace
