
#pragma once

#include <propertyguizeug/propertyguizeug.h>

#include <QTreeView>

namespace zeug {
    
class PropertyGroup;
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
