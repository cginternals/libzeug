
#pragma once

#include <QTreeView>

#include <propertyguizeug/propertyguizeug.h>

namespace reflectionzeug {
    class PropertyGroup;
}


namespace propertyguizeug
{

class PropertyModel;
class PropertyDelegate;

class PROPERTYGUIZEUG_API PropertyBrowser : public QTreeView
{
public:
    PropertyBrowser(reflectionzeug::PropertyGroup * root, QWidget * parent = nullptr);
    ~PropertyBrowser();

protected:
    PropertyModel * m_model;
    PropertyDelegate * m_delegate;
    
};
    
} // namespace propertyguizeug
