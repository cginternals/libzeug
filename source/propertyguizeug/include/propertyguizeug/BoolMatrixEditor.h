
#pragma once

#include <QStringList>

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/MatrixEditor.h>

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API BoolMatrixEditor : public MatrixEditor
{
public:
    BoolMatrixEditor(reflectionzeug::Property<std::vector<bool>> * property, QWidget * parent = nullptr);
    virtual ~BoolMatrixEditor();
    
    bool stringToBool(const QString & string) const;
    
    virtual void setMatrix();

protected:
    QString valueRegexString() const;
    QStringList trueValues() const;
    QStringList falseValues() const;
    
    reflectionzeug::Property<std::vector<bool>> * m_property;
    
};

} // namespace propertyguizeug
