
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/PropertyEditor.h>

class QWidget;

namespace reflectionzeug
{

class StringPropertyInterface;

} // namespace reflectionzeug

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
    StringEditor(reflectionzeug::StringPropertyInterface * property, QWidget * parent = nullptr);

protected:
    QWidget * createComboBox();
    QWidget * createLineEdit();
    
    void setString(const QString & text);

protected:    
    reflectionzeug::StringPropertyInterface * m_property;
    
};

} // namespace propertyguizeug
