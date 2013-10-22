
#pragma once

#include <QStyledItemDelegate>

#include <propertyguizeug/propertyguizeug.h>

#include <propertyguizeug/PropertyEditorFactory.h>
#include <propertyguizeug/PropertyPainter.h>


namespace zeug {
    
class AbstractProperty;

class PROPERTYGUIZEUG_API PropertyDelegate : public QStyledItemDelegate
{
public:
    PropertyDelegate(QWidget * parent = nullptr);
    virtual ~PropertyDelegate();
    
    virtual void paint(QPainter * painter,
                       const QStyleOptionViewItem & option,
                       const QModelIndex & index) const;
    
    virtual QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option,
                                   const QModelIndex & index) const;
    
    virtual void setEditorData(QWidget * editor, const QModelIndex & index) const;
    
    virtual void setModelData(QWidget * editor, QAbstractItemModel * model,
                              const QModelIndex & index) const;
    
    virtual void updateEditorGeometry(QWidget * editor,
                                      const QStyleOptionViewItem & option,
                                      const QModelIndex &index) const;
    
    virtual QSize sizeHint(const QStyleOptionViewItem & option,
                            const QModelIndex & index) const;

protected:
    mutable PropertyEditorFactory m_editorFactory;
    mutable PropertyPainter m_propertyPainter;
};
    
} // namespace zeug
