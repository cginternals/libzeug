
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <functional>
#include <QWidget>

class QLineEdit;

namespace zeug {

class PROPERTYGUIZEUG_API MatrixEditor : public QWidget
{
public:
    MatrixEditor(int matrixSize,
                 const QString & valueRegexString,
                 const QString & initialText,
                 QWidget * parent = nullptr);
    
    virtual ~MatrixEditor();
    
    QRegExp matrixRegex(int matrixSize, const QString & valueRegexString) const;
    void valuesFromText(const std::function<void(const QString &)> & functor) const;
    
    virtual void setMatrix() = 0;
    
protected:
    QLineEdit * m_lineEdit;
    
    QString m_valueRegexString;
};

} // namespace
