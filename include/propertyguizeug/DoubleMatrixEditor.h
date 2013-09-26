
#pragma once

#include "MatrixEditor.h"

namespace propertyguizeug {

using namespace propertyzeug;

class PROPERTYGUIZEUG_API DoubleMatrixEditor : public MatrixEditor
{
public:
    DoubleMatrixEditor(Property<std::vector<double>> * property, QWidget * parent = nullptr);
    virtual ~DoubleMatrixEditor();
    
    void setMatrix();

protected:
    Property<std::vector<double>> * m_property;
    
};

} // namespace
