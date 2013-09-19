
#include <QApplication>
#include <QPainter>
#include <propertyguizeug/PropertyDelegate.h>

namespace propertyguizeug {
    
PropertyDelegate::PropertyDelegate(QWidget * parent)
:   QStyledItemDelegate(parent)
{
}
    
PropertyDelegate::~PropertyDelegate()
{
}
    
void PropertyDelegate::paint(QPainter * painter,
   const QStyleOptionViewItem & option,
   const QModelIndex & index) const
{
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
    
    if (property->isGroup())
        return QStyledItemDelegate::paint(painter, option, index);
    
    if (m_propertyPainter.drawValue(painter, option, *property))
        return;
    
    QStyleOptionViewItem myOption = option;
    QString text = QString::fromStdString(property->valueAsString());
    myOption.text = text;
    QStyledItemDelegate::paint(painter, myOption, index);
}
    
QWidget * PropertyDelegate::createEditor(QWidget * parent,
    const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
    
    if (property->isGroup())
        return QStyledItemDelegate::createEditor(parent, option, index);
    
    return const_cast<PropertyDelegate *>(this)->createEditorForProperty(parent, property);
}

void PropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
}

void PropertyDelegate::setModelData(QWidget * editor, QAbstractItemModel * model,
    const QModelIndex & index) const
{
}

void PropertyDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option,
    const QModelIndex & index) const
{
    editor->setGeometry(option.rect);
}
    
QSize PropertyDelegate::sizeHint (const QStyleOptionViewItem & option,
    const QModelIndex & index) const
{
    return QSize(100, 30);
}
    
QWidget * PropertyDelegate::createEditorForProperty(QWidget * parent, AbstractProperty * property)
{
    QWidget * editor = m_editorFactory.createEditor(*property);
    editor->setParent(parent);
    return editor;
}

    
} // namespace
