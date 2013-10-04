
#pragma once

#include <QStringList>

#include "MatrixEditor.h"

namespace zeug {

template <typename Type>
class Property;

class PROPERTYGUIZEUG_API BoolMatrixEditor : public MatrixEditor
{
public:
    BoolMatrixEditor(Property<std::vector<bool>> * property, QWidget * parent = nullptr);
    virtual ~BoolMatrixEditor();
    
    bool stringToBool(const QString & string) const;
    
    virtual void setMatrix();

protected:
    QString valueRegexString() const;
    QStringList trueValues() const;
    QStringList falseValues() const;
    
    Property<std::vector<bool>> * m_property;
    
};

} // namespace
