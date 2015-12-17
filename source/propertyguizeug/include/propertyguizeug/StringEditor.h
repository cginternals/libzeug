#pragma once

#include <reflectionzeug/property/property_declaration.h>

#include <signalzeug/ScopedConnection.h>

#include <propertyguizeug/PropertyEditor.h>
#include <propertyguizeug/ChoicesModel.h>

class QWidget;

namespace reflectionzeug
{
    class AbstractStringInterface;
}

namespace propertyguizeug
{

/** \brief Editor for strings
 *
 * Supported options
 * - choices (std::vector<std::string>): list of choices; when set, editor will be a combobox.
 * - deferred (bool): defer changing the property's value until enter is pressed (only for plain edits)
 */
class PROPERTYGUIZEUG_API StringEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::AbstractStringInterface;
    
public:
    StringEditor(reflectionzeug::AbstractStringInterface * property, 
                 QWidget * parent = nullptr);
    virtual ~StringEditor();

private:
    QWidget * createComboBox();
    QWidget * createLineEdit();

    void setString(const QString & text);

private:
    reflectionzeug::AbstractStringInterface * m_property;
    ChoicesModel * m_model;
    signalzeug::ScopedConnection m_propertyChangedConnection;
};

} // namespace propertyguizeug
