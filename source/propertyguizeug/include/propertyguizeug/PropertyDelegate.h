
#pragma once

#include <QStyledItemDelegate>

#include <propertyguizeug/propertyguizeug_api.h>


namespace propertyguizeug
{

class PropertyEditorFactory;
class PropertyPainter;

class PROPERTYGUIZEUG_API PropertyDelegate : public QStyledItemDelegate
{
public:
    PropertyDelegate(PropertyEditorFactory * editorFactory,
                     PropertyPainter * painter,
                     QWidget * parent = nullptr);

    virtual ~PropertyDelegate();

    virtual void paint(QPainter * painter,
                       const QStyleOptionViewItem & option,
                       const QModelIndex & index) const;

    virtual QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option,
                                   const QModelIndex & index) const;

    virtual void updateEditorGeometry(QWidget * editor,
                                      const QStyleOptionViewItem & option,
                                      const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem & option,
                            const QModelIndex & index) const;

protected:
    PropertyEditorFactory * m_editorFactory;
    PropertyPainter * m_propertyPainter;
    
};

} // namespace propertyguizeug
