
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <functional>
#include <QLineEdit>

namespace zeug {

class PROPERTYGUIZEUG_API MatrixEditor : public QLineEdit
{
public:
    MatrixEditor(int matrixSize, const QString & valueRegexString,
                 QWidget * parent = nullptr);
    
    virtual ~MatrixEditor();
    
    QRegExp matrixRegex(int matrixSize, const QString & valueRegexString) const;
    void valuesFromText(const std::function<void(const QString &)> & functor) const;
    
protected:
    QString m_valueRegexString;
};

} // namespace
