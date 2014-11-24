#pragma once

#include <QStyledItemDelegate>

#include <propertyguizeug/propertyguizeug_api.h>

namespace propertyguizeug
{

class AbstractPropertyEditorPlugin;
class AbstractPropertyPainterPlugin;
class PropertyEditorFactory;
class PropertyPainter;

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

    virtual void updateEditorGeometry(QWidget * editor,
                                      const QStyleOptionViewItem & option,
                                      const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem & option,
                            const QModelIndex & index) const;
                            
    void addEditorPlugin(AbstractPropertyEditorPlugin * plugin);
    void addPainterPlugin(AbstractPropertyPainterPlugin * plugin);

private:
    PropertyEditorFactory * m_editorFactory;
    PropertyPainter * m_propertyPainter;
};

} // namespace propertyguizeug
