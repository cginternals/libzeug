#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>

class QWidget;

namespace reflectionzeug
{
    class StringPropertyInterface;
}

namespace propertyguizeug
{

/** \brief Editor for strings
 *
 * Supported options
 * - choices (std::vector<std::string>): list of choices; when set, editor will be a combobox.
 */
class PROPERTYGUIZEUG_API StringEditor : public PropertyEditor
{
public:
    using Type = reflectionzeug::StringPropertyInterface;
    
public:
    StringEditor(reflectionzeug::StringPropertyInterface * property, 
                 QWidget * parent = nullptr);

private:
    QWidget * createComboBox();
    QWidget * createLineEdit();
    
    void setString(const QString & text);

private:    
    reflectionzeug::StringPropertyInterface * m_property;
};

} // namespace propertyguizeug
