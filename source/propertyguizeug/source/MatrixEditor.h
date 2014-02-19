
#pragma once

#include <functional>

#include <propertyguizeug/propertyguizeug.h>

#include "PropertyEditor.h"


class QLineEdit;

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API MatrixEditor : public PropertyEditor
{
public:
    MatrixEditor(int matrixSize,
                 const QString & valueRegexString,
                 const QString & initialText,
                 QWidget * parent = nullptr);
    
    virtual ~MatrixEditor();

    
    QRegularExpression matrixRegex() const;
    void valuesFromText(const std::function<void(const QString &)> & functor) const;
    
    virtual void setMatrix() = 0;
    
    void parseString();
    bool textMatchesRegex();
    
protected:
    QLineEdit * m_lineEdit;
    
    QString m_valueRegexString;
    int m_matrixSize;
};

} // namespace propertyguizeug
