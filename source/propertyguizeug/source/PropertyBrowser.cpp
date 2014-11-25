#include <propertyguizeug/PropertyBrowser.h>

#include <cassert>

#include <QWindow>
#include <QScreen>

#include <reflectionzeug/AbstractProperty.h>

#include <propertyguizeug/PropertyModel.h>
#include <propertyguizeug/PropertyDelegate.h>

#include "PropertyItem.h"

using namespace reflectionzeug;

namespace
{

AbstractProperty * retrieveProperty(const QModelIndex & index)
{
    return static_cast<propertyguizeug::PropertyItem *>(index.internalPointer())->property();
}
    
} // namespace

namespace propertyguizeug
{
    
PropertyBrowser::PropertyBrowser(QWidget * parent)
:   PropertyBrowser{nullptr, parent}
{
}

PropertyBrowser::PropertyBrowser(
    PropertyGroup * root,
    QWidget * parent)
:   QTreeView(parent)
,   m_delegate{new PropertyDelegate{this}}
,   m_alwaysExpandGroups{false}
{
    setRoot(root);
    setItemDelegateForColumn(1, m_delegate);
    
    initView();
}

PropertyBrowser::~PropertyBrowser()
{
    delete model();
}
    
void PropertyBrowser::setRoot(reflectionzeug::PropertyGroup * root)
{   
    QAbstractItemModel * newModel = (root == nullptr) ? nullptr : new PropertyModel(root);

    auto model = this->model();
    setModel(newModel);
    delete model;

    if (m_alwaysExpandGroups && newModel)
    {
        connect(newModel, &QAbstractItemModel::rowsInserted,
                this, &PropertyBrowser::onRowsInserted);

        expandAllGroups();
    }
}

void PropertyBrowser::setAlwaysExpandGroups(bool b)
{
    m_alwaysExpandGroups = b;
}

void PropertyBrowser::showEvent(QShowEvent * event)
{    
    auto window = windowHandle();
    
    if (!window)
        window = nativeParentWidget()->windowHandle();

    connect(window, &QWindow::screenChanged, 
            this, &PropertyBrowser::reset,
            Qt::UniqueConnection);
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
            expand(index);
    }
}

void PropertyBrowser::addEditorPlugin(AbstractPropertyEditorPlugin * plugin)
{
    m_delegate->addEditorPlugin(plugin);
}

void PropertyBrowser::addPainterPlugin(AbstractPropertyPainterPlugin * plugin)
{
    m_delegate->addPainterPlugin(plugin);
}
    
void PropertyBrowser::initView()
{
    setEditTriggers(QAbstractItemView::AllEditTriggers);
    setAlternatingRowColors(true);
    setUniformRowHeights(true);
    setTabKeyNavigation(true);
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
            expand(index);
    }
}

} // namespace propertyguizeug
