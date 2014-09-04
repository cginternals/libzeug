
#include <cassert>

#include <reflectionzeug/AbstractProperty.h>

#include <propertyguizeug/PropertyModel.h>
#include <propertyguizeug/PropertyDelegate.h>
#include <propertyguizeug/PropertyEditorFactory.h>
#include <propertyguizeug/PropertyPainter.h>

#include <propertyguizeug/PropertyBrowser.h>

#include "PropertyItem.h"


using namespace reflectionzeug;

namespace propertyguizeug
{
    
PropertyBrowser::PropertyBrowser(QWidget * parent)
:   PropertyBrowser(new PropertyEditorFactory(),
                    new PropertyPainter(),
                    parent)
{
    
}

PropertyBrowser::PropertyBrowser(
    PropertyGroup * root,
    QWidget * parent)
:   PropertyBrowser(root,
                    new PropertyEditorFactory(),
                    new PropertyPainter(),
                    parent)
{
}
    
PropertyBrowser::PropertyBrowser(
    PropertyEditorFactory * editorFactory,
    PropertyPainter * painter,
    QWidget * parent)
:   QTreeView(parent)
,   m_delegate(new PropertyDelegate(editorFactory, painter, this))
,   m_alwaysExpandGroups(false)
{
    this->setRoot(nullptr);
    this->setItemDelegateForColumn(1, m_delegate);
    
    initView();
}
    
PropertyBrowser::PropertyBrowser(
    PropertyGroup * root,
    PropertyEditorFactory * editorFactory,
    PropertyPainter * painter,
    QWidget * parent)
:   QTreeView(parent)
,   m_delegate(new PropertyDelegate(editorFactory, painter, this))
,   m_alwaysExpandGroups(false)
{
    this->setRoot(root);
    this->setItemDelegateForColumn(1, m_delegate);
    
    initView();
}

PropertyBrowser::~PropertyBrowser()
{
    delete this->model();
}
    
void PropertyBrowser::setRoot(reflectionzeug::PropertyGroup * root)
{   
    QAbstractItemModel * newModel = (root == nullptr) ? nullptr : new PropertyModel(root);

    QAbstractItemModel * model = this->model();
    this->setModel(newModel);
    delete model;

    if (m_alwaysExpandGroups && newModel)
    {
        connect(newModel, &QAbstractItemModel::rowsInserted,
                this, &PropertyBrowser::onRowsInserted);

        this->expandAllGroups();
    }
}

void PropertyBrowser::onRowsInserted(const QModelIndex & parentIndex, int first, int last)
{
    QAbstractItemModel * model = this->model();

    for (int i = first; i <= last; ++i)
    {
        QModelIndex index = model->index(i, 0, parentIndex);

        if (!index.isValid())
            continue;

        AbstractProperty * property = retrieveProperty(index);

        if (property->isGroup() && model->hasChildren(index))
            this->expand(index);
    }
}

void PropertyBrowser::setAlwaysExpandGroups(bool b)
{
    m_alwaysExpandGroups = b;
}
    
void PropertyBrowser::initView()
{
    this->setEditTriggers(QAbstractItemView::AllEditTriggers);
    this->setAlternatingRowColors(true);
    this->setUniformRowHeights(true);
    this->setTabKeyNavigation(true);
}

void PropertyBrowser::expandAllGroups()
{
    QAbstractItemModel * model = this->model();

    QModelIndexList indexes = model->match(model->index(0,0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard|Qt::MatchRecursive);
    for (QModelIndex index : indexes)
    {
        if (!index.isValid())
            continue;

        AbstractProperty * property = retrieveProperty(index);

        if (property->isGroup() && model->hasChildren(index))
            this->expand(index);
    }
}

} // namespace propertyguizeug
