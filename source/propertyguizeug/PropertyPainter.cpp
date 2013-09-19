
#include <QApplication>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <propertyguizeug/PropertyPainter.h>

namespace propertyguizeug {
    
PropertyPainter::PropertyPainter()
:   m_drawn(false)
,   m_painter(nullptr)
{
}

PropertyPainter::~PropertyPainter()
{
}

bool PropertyPainter::drawValue(QPainter * painter, 
    const QStyleOptionViewItem & option, AbstractProperty & property)
{
    m_drawn = false;
    m_painter = painter;
    m_option = option;

    property.accept(*this);

    return m_drawn;
}

void PropertyPainter::visit(Property<bool> & property)
{
    QStyleOptionButton opt;
    opt.state = property.value() ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    opt.rect = m_option.rect;
    
    if (m_option.state & QStyle::State_Selected)
        m_painter->fillRect(m_option.rect, m_option.palette.highlight());
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &opt, m_painter);
    
    m_drawn = true;
}
    
void PropertyPainter::visit(Property<int> & property)
{

}
    
void PropertyPainter::visit(Property<double> & property)
{

}
    
void PropertyPainter::visit(Property<std::string> & property)
{

}

void PropertyPainter::visit(Property<Color> & property)
{

}

void PropertyPainter::visit(Property<FilePath> & property)
{

}

void PropertyPainter::visit(Property<std::vector<bool>> & property)
{

}

void PropertyPainter::visit(Property<std::vector<int>> & property)
{

}

void PropertyPainter::visit(Property<std::vector<double>> & property)
{

}

void PropertyPainter::visit(PropertyGroup & property)
{

}
    
} // namespace
