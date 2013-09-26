
#pragma once

#include "MatrixEditor.h"

namespace propertyguizeug {

using namespace propertyzeug;

class PROPERTYGUIZEUG_API IntMatrixEditor : public MatrixEditor
{
public:
    IntMatrixEditor(Property<std::vector<int>> * property, QWidget * parent = nullptr);
    virtual ~IntMatrixEditor();
    
    void setMatrix();

protected:
    Property<std::vector<int>> * m_property;
    
};

} // namespace
