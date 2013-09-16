
#pragma once

#include <QTreeView>
#include <propertyzeug/PropertyGroup.h>
#include "propertyguizeug.h"

namespace propertyguizeug {

class PropertyItemModel;
class PropertyDelegate;

using propertyzeug::PropertyGroup;

class PROPERTYGUIZEUG_API PropertyBrowser : public QTreeView
{
public:
    PropertyBrowser(PropertyGroup & root, QWidget * parent = nullptr);
    ~PropertyBrowser();

protected:
    PropertyItemModel * m_model;
    PropertyDelegate * m_delegate;
    
};
    
} // namespace
