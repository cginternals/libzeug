
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>
#include <reflectionzeug/StringPropertyInterface.h>

#include <signalzeug/ScopedConnection.h>

class QComboBox;

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API ChoiceEditor : public PropertyEditor
{
public:
    ChoiceEditor(reflectionzeug::StringPropertyInterface * property, QWidget * parent = nullptr);
    virtual ~ChoiceEditor();

    void setString(const QString & text);

protected:
    void propertyChoicesChanged(const std::vector<std::string> & choices);

protected:
    reflectionzeug::StringPropertyInterface * m_property;
    QComboBox * m_comboBox;
    signalzeug::ScopedConnection m_connection;
};

} // namespace propertyguizeug
