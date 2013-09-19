
#pragma once

#include <QStyledItemDelegate>
#include <propertyzeug/Property.h>
#include <propertyguizeug/PropertyEditorFactory.h>
#include "propertyguizeug.h"

namespace propertyguizeug {
    
using namespace propertyzeug;

class PropertyDelegate : public QStyledItemDelegate
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
    
    virtual QSize sizeHint (const QStyleOptionViewItem & option,
                            const QModelIndex & index) const;

protected:
    QWidget * createEditorForProperty(QWidget * parent, AbstractProperty * property);
    
    PropertyEditorFactory m_editorFactory;
};
    
} // namespace 
