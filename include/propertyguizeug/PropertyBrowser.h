
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QTreeView>

namespace propertyzeug {
    class PropertyGroup;
}

namespace propertyguizeug {
    
using propertyzeug::PropertyGroup;

class PropertyModel;
class PropertyDelegate;

class PROPERTYGUIZEUG_API PropertyBrowser : public QTreeView
{
public:
    PropertyBrowser(PropertyGroup * root, QWidget * parent = nullptr);
    ~PropertyBrowser();

protected:
    PropertyModel * m_model;
    PropertyDelegate * m_delegate;
    
};
    
} // namespace
