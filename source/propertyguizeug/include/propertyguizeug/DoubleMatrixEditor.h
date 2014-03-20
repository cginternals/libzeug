
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/MatrixEditor.h>

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API DoubleMatrixEditor : public MatrixEditor
{
public:
    DoubleMatrixEditor(reflectionzeug::Property<std::vector<double>> * property, QWidget * parent = nullptr);
    virtual ~DoubleMatrixEditor();
    
    virtual void setMatrix();

protected:
    reflectionzeug::Property<std::vector<double>> * m_property;
    
};

} // namespace propertyguizeug
