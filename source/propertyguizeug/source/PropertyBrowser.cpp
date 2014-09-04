
#include <cassert>

#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/AbstractValueProperty.h>

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
{
    this->setModel(nullptr);
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
{
    this->setModel(new PropertyModel(root));
    this->setItemDelegateForColumn(1, m_delegate);
    
    initView();
}

PropertyBrowser::~PropertyBrowser()
{
    delete this->model();
}
    
void PropertyBrowser::setRoot(reflectionzeug::PropertyGroup * root)
{   
    QAbstractItemModel * model = this->model();
    this->setModel((root == nullptr) ? nullptr : new PropertyModel(root));
    delete model;
}
    
void PropertyBrowser::initView()
{
    this->setEditTriggers(QAbstractItemView::AllEditTriggers);
    this->setAlternatingRowColors(true);
    this->setUniformRowHeights(true);
    this->setTabKeyNavigation(true);
}

} // namespace propertyguizeug
