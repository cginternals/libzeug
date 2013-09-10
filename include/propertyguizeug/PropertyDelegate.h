
#pragma once

#include <QStyledItemDelegate>
#include "propertyguizeug.h"

namespace propertyguizeug {

class PropertyDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    
public:
    PropertyDelegate(QWidget * parent = nullptr);
    virtual ~PropertyDelegate();
    
    void paint(QPainter * painter, const QStyleOptionViewItem & option,
               const QModelIndex & index) const;

};
    
} // namespace 
