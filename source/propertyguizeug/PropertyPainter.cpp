
#include <QApplication>
#include <QPainter>
#include <QStyleOptionViewItem>

#include <propertyguizeug/PropertyPainter.h>
#include <propertyguizeug/TransparencyBackgroundBrush.hpp>


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
    if (m_option.state & QStyle::State_Selected)
        m_painter->fillRect(m_option.rect, m_option.palette.highlight());
    
    const Color & color = property.value();
    
    QPixmap pixmap(20, 20);
    pixmap.fill(QColor(
                    color.red(),
                    color.green(),
                    color.blue(),
                    color.alpha()
                ));
    
    QRect pixmapRect = m_option.rect;
    pixmapRect.setLeft(pixmapRect.left() + 5);
    pixmapRect.setTop(pixmapRect.top() + 4);
    pixmapRect.setWidth(20);
    pixmapRect.setHeight(20);
    
    m_painter->fillRect(pixmapRect, TransparencyBackgroundBrush());
    m_painter->drawPixmap(pixmapRect, pixmap);
    
    QRect rect = m_option.rect;
    rect.setLeft(pixmapRect.right() + 7);
    
    QApplication::style()->drawItemText(m_painter,
                                        rect,
                                        Qt::AlignVCenter,
                                        m_option.palette,
                                        true,
                                        QString::fromStdString(property.valueAsString()),
                                        QPalette::Text);
    
    m_drawn = true;
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
