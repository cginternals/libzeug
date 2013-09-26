
#pragma once

#include <functional>
#include <QLineEdit>
#include <propertyzeug/Property.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

using namespace propertyzeug;

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
