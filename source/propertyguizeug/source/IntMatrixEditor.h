
#pragma once

#include "MatrixEditor.h"

namespace zeug 
{
    
template <typename Type>
class Property;

class PROPERTYGUIZEUG_API IntMatrixEditor : public MatrixEditor
{
public:
    IntMatrixEditor(Property<std::vector<int>> * property, QWidget * parent = nullptr);
    virtual ~IntMatrixEditor();
    
    virtual void setMatrix();

protected:
    Property<std::vector<int>> * m_property;
    
};

} // namespace
