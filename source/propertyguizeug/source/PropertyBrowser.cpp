
#include <cassert>

#include <QClipboard>
#include <QGuiApplication>
#include <QCursor>
#include <QKeyEvent>

#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/AbstractValueProperty.h>

#include <propertyguizeug/PropertyModel.h>
#include <propertyguizeug/PropertyDelegate.h>
#include <propertyguizeug/PropertyEditorFactory.h>
#include <propertyguizeug/PropertyPainter.h>

#include <propertyguizeug/PropertyBrowser.h>

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

void PropertyBrowser::keyPressEvent(QKeyEvent * event)
{
    if (event->modifiers() != Qt::ControlModifier)
        return QTreeView::keyPressEvent(event);
    
    if (!(event->key() == Qt::Key_C || event->key() == Qt::Key_V))
        return QTreeView::keyPressEvent(event);
        
    QModelIndex index = this->indexAt(viewport()->mapFromGlobal(QCursor::pos()));
    if (!index.isValid())
        return QTreeView::keyPressEvent(event);
            
    AbstractProperty * property = retrieveProperty(index);
    if (!property->isValue())
        return QTreeView::keyPressEvent(event);
        
    AbstractValueProperty * valueProperty = property->asValue();
    QClipboard * clipboard = QGuiApplication::clipboard();
    
    if (event->key() == Qt::Key_C)
        clipboard->setText(QString::fromStdString(valueProperty->toString()));
    else if (event->key() == Qt::Key_V)
        valueProperty->fromString(clipboard->text().toStdString());
}

} // namespace propertyguizeug
