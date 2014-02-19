

#include <propertyguizeug/PropertyModel.h>
#include <propertyguizeug/PropertyDelegate.h>

#include <propertyguizeug/PropertyBrowser.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyBrowser::PropertyBrowser(PropertyGroup * root, QWidget * parent)
:   QTreeView(parent)
,   m_model(new PropertyModel(root, this))
,   m_delegate(new PropertyDelegate(this))
{
    this->setModel(m_model);
    this->setItemDelegateForColumn(1, m_delegate);
    this->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed | QAbstractItemView::CurrentChanged);
    this->setAlternatingRowColors(true);
    this->setUniformRowHeights(true);
    this->setColumnWidth(0, 150);
    this->setColumnWidth(1, 200);
    this->expandAll();
}

PropertyBrowser::~PropertyBrowser()
{
}

} // namespace propertyguizeug
