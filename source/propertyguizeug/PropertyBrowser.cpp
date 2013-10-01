
#include <propertyguizeug/PropertyBrowser.h>

#include <propertyguizeug/PropertyModel.h>
#include <propertyguizeug/PropertyDelegate.h>

namespace propertyguizeug {
    
PropertyBrowser::PropertyBrowser(PropertyGroup * root, QWidget * parent)
:   QTreeView(parent)
,   m_model(new PropertyModel(root, this))
,   m_delegate(new PropertyDelegate(this))
{
    this->setModel(m_model);
    this->setItemDelegateForColumn(1, m_delegate);
    
    this->setAlternatingRowColors(true);
    this->setUniformRowHeights(true);
    this->setColumnWidth(0, 150);
    this->setColumnWidth(1, 200);
    this->expandAll();
}

PropertyBrowser::~PropertyBrowser()
{
}

} // namespace
