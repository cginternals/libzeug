
#pragma once

#include <functional>
#include <set>

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"


class QLineEdit;

namespace zeug 
{

class PROPERTYGUIZEUG_API SetEditor : public PropertyEditor
{
public:
    SetEditor(const QString & valueRegexString,
                 const QString & initialText,
                 QWidget * parent = nullptr);
    
    virtual ~SetEditor();

    
    QRegularExpression setRegex() const;
    void valuesFromText(const std::function<void(const QString &)> & functor) const;
    
    virtual void setSet() = 0;
    
    void parseString();
    bool textMatchesRegex();
    
protected:
    QLineEdit * m_lineEdit;
    
    QString m_valueRegexString;
};

} // namespace
