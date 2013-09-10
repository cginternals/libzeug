
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
    const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}
    
} // namespace
