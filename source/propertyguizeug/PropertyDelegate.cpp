
#include <propertyzeug/AbstractProperty.h>
#include <propertyguizeug/PropertyType.h>
#include <propertyguizeug/NumberEditor.h>
#include <propertyguizeug/StringEditor.h>
#include <propertyguizeug/PropertyDelegate.h>

namespace propertyguizeug {
  
using namespace propertyzeug;
    
PropertyDelegate::PropertyDelegate(QWidget * parent)
:   QStyledItemDelegate(parent)
,   m_activeEditor(nullptr)
{
}
    
PropertyDelegate::~PropertyDelegate()
{
}
    
QWidget * PropertyDelegate::createEditor(QWidget * parent,
    const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
    
    if (!property->isGroup())
        return const_cast<PropertyDelegate *>(this)->createEditorForProperty(parent, property);
    
    return QStyledItemDelegate::createEditor(parent, option, index);
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

QWidget * PropertyDelegate::createEditorForProperty(QWidget * parent, AbstractProperty * property)
{
    property->accept(*this);
    m_activeEditor->setParent(parent);
    return m_activeEditor;
}
    
QSize PropertyDelegate::sizeHint (const QStyleOptionViewItem & option,
    const QModelIndex & index) const
{
    return QSize(100, 30);
}

void PropertyDelegate::visit(Property<int> & property)
{
    m_activeEditor = new NumberEditor<int>(&property);
}
    
void PropertyDelegate::visit(Property<std::string> & property)
{
    m_activeEditor = new StringEditor(&property);
}
    
} // namespace
