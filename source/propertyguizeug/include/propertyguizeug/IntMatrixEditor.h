
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <propertyguizeug/MatrixEditor.h>

namespace propertyguizeug
{
    
class PROPERTYGUIZEUG_API IntMatrixEditor : public MatrixEditor
{
public:
    IntMatrixEditor(reflectionzeug::Property<std::vector<int>> * property, QWidget * parent = nullptr);
    virtual ~IntMatrixEditor();
    
    virtual void setMatrix();

protected:
    reflectionzeug::Property<std::vector<int>> * m_property;
    
};

} // namespace propertyguizeug
