
#include <cassert>

#include <reflectionzeug/AbstractProperty.h>

#include <propertyguizeug/PropertyEditorFactory.h>
#include <propertyguizeug/PropertyPainter.h>
#include <propertyguizeug/PropertyDelegate.h>

using namespace reflectionzeug;
namespace propertyguizeug
{

PropertyDelegate::PropertyDelegate(
    PropertyEditorFactory * editorFactory,
    PropertyPainter * painter,
    QWidget * parent)
:   QStyledItemDelegate(parent)
,   m_editorFactory(editorFactory)
,   m_propertyPainter(painter)
{
    assert(m_editorFactory != nullptr);
    assert(m_propertyPainter != nullptr);
}

PropertyDelegate::~PropertyDelegate()
{
    delete m_editorFactory;
    delete m_propertyPainter;
}

void PropertyDelegate::paint(QPainter * painter,
   const QStyleOptionViewItem & option,
   const QModelIndex & index) const
{
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());

    if (property->isGroup())
        return QStyledItemDelegate::paint(painter, option, index);

	QStyleOptionViewItem opt = option;
	this->initStyleOption(&opt, index);

	m_propertyPainter->drawValue(painter, opt, *property->asValue());
}

QWidget * PropertyDelegate::createEditor(QWidget * parent,
    const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());

    if (property->isGroup())
        return QStyledItemDelegate::createEditor(parent, option, index);

    return m_editorFactory->createEditorWithParent(*property->asValue(), parent);
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
    return QSize(100, 27);
}

} // namespace propertyguizeug
