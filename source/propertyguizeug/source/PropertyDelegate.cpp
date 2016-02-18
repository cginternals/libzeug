#include <propertyguizeug/PropertyDelegate.h>

#include <cassert>

#include <QApplication>

#include <reflectionzeug/property/AbstractProperty.h>

#include <propertyguizeug/PropertyEditorFactory.h>
#include <propertyguizeug/PropertyPainter.h>

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

PropertyDelegate::PropertyDelegate(QWidget * parent)
:   QStyledItemDelegate{parent}
,   m_editorFactory{new PropertyEditorFactory{}}
,   m_propertyPainter{new PropertyPainter{}}
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
    QStyledItemDelegate::paint(painter, option, index);

	AbstractProperty * property = retrieveProperty(index);

	if (property->isCollection())
		return;

	QStyleOptionViewItem opt = option;
	initStyleOption(&opt, index);

	m_propertyPainter->drawValue(painter, opt, *property);
}

QWidget * PropertyDelegate::createEditor(QWidget * parent,
    const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    AbstractProperty * property = retrieveProperty(index);

    if (property->isCollection())
        return QStyledItemDelegate::createEditor(parent, option, index);

    return m_editorFactory->createEditor(*property, parent);
}

void PropertyDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option,
    const QModelIndex & /*index*/) const
{
    editor->setGeometry(option.rect);
}

QSize PropertyDelegate::sizeHint(const QStyleOptionViewItem & option,
    const QModelIndex & index) const
{
    auto size = QStyledItemDelegate::sizeHint(option, index);
	return {size.width(), static_cast<int>(size.height() * 1.5)};
}

void PropertyDelegate::addEditorPlugin(AbstractPropertyEditorPlugin * plugin)
{
    m_editorFactory->addPlugin(plugin);
}

void PropertyDelegate::addPainterPlugin(AbstractPropertyPainterPlugin * plugin)
{
    m_propertyPainter->addPlugin(plugin);
}

} // namespace propertyguizeug
