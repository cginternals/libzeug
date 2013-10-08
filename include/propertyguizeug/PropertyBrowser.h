
#pragma once

#include <QTreeView>

#include <propertyguizeug/propertyguizeug.h>

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
    
} // namespace zeug
