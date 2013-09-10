
#include <propertyzeug/AbstractProperty.h>
#include <propertyguizeug/PropertyType.h>
#include <propertyguizeug/PropertyDelegate.h>

namespace propertyguizeug {
  
using namespace propertyzeug;
    
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

}
    
} // namespace
