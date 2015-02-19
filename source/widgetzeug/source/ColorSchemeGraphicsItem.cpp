
#include "ColorSchemeGraphicsItem.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>
#include <QPainter>
#include <QApplication>
#include <QScreen>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QToolTip>

#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/DpiAwareGraphicsView.h>
#include <widgetzeug/RGBABrush.hpp>


namespace widgetzeug
{

const QBrush ColorSchemeGraphicsItem::s_selectedBrush   = QColor("#b0b0b0");
const QBrush ColorSchemeGraphicsItem::s_hoveredBrush    = QColor("#d0d0d0");
const QPen ColorSchemeGraphicsItem::s_pen               = QColor("#d0d0d0");

ColorSchemeGraphicsItem::ColorSchemeGraphicsItem(
    const DpiAwareGraphicsView * view, 
    ColorScheme * scheme,
    QGraphicsItem * parent) 
:   QGraphicsObject(parent)
,   m_view{ view }
,   m_scheme{ scheme }
,   m_deficiency{ ColorScheme::None }
,   m_frame{ new QGraphicsRectItem(this) }
,   m_rectSize{ 15, 15 } // + 1px outline each -> 16x16
,   m_padding{ 2.0 }
,   m_selected{ false }
,   m_detailedTooltip{ false }
{
    setAcceptHoverEvents(true);

    m_frame->setBrush(Qt::NoBrush);
    m_frame->setPen(Qt::NoPen);

    setClasses(5);
}

ColorSchemeGraphicsItem::~ColorSchemeGraphicsItem()
{
    qDeleteAll(m_rects);
    delete m_frame;
}

void ColorSchemeGraphicsItem::setScheme(ColorScheme * scheme)
{
    m_scheme = scheme;
    updateBrushes();
    updateTooltips();
}

ColorScheme * ColorSchemeGraphicsItem::scheme()
{
    return m_scheme;
}

void ColorSchemeGraphicsItem::setClasses(const int classes)
{
    if (m_scheme)
        m_classes = qBound<int>(m_scheme->minClasses(), classes, m_scheme->maxClasses());
    else
        m_classes = classes;

    updateRects();
}

int ColorSchemeGraphicsItem::classes() const
{
    return m_classes;
}

void ColorSchemeGraphicsItem::setDeficiency(const ColorScheme::ColorVisionDeficiency deficiency)
{
    if (deficiency == m_deficiency)
        return;

    m_deficiency = deficiency;
    updateBrushes();
}

ColorScheme::ColorVisionDeficiency ColorSchemeGraphicsItem::deficiency() const
{
    return m_deficiency;
}

void ColorSchemeGraphicsItem::setPadding(const qreal padding)
{
    if (padding == m_padding)
        return;

    m_padding = padding;
    updateRects();
}

qreal ColorSchemeGraphicsItem::padding() const
{
    return m_padding;
}

void ColorSchemeGraphicsItem::setRectSize(const QSizeF & size)
{
    if (size == m_rectSize)
        return;

    m_rectSize = size;
    updateRects();
}

const QSizeF & ColorSchemeGraphicsItem::rectSize() const
{
    return m_rectSize;
}

void ColorSchemeGraphicsItem::setSelected(bool selected, bool signal)
{
    if (selected == m_selected)
        return;

    m_selected = selected;
    m_frame->setBrush(m_selected ? s_selectedBrush : Qt::NoBrush);
    
    if (selected && signal)
        emit this->selected(m_scheme);
        
    update();
}

bool ColorSchemeGraphicsItem::isSelected() const
{
    return m_selected;
}

void ColorSchemeGraphicsItem::setDetailedTooltip(bool active)
{
    m_detailedTooltip = active;
    updateTooltips();
}

bool ColorSchemeGraphicsItem::detailedTooltip() const
{
    return m_detailedTooltip;
}

void ColorSchemeGraphicsItem::updateRects()
{
    qDeleteAll(m_rects);
    m_rects.clear();

    const QSize rectSize = m_rectSize.toSize() * m_view->dpiBasedScale();
    const int padding  = m_padding * m_view->dpiBasedScale(); // this is required to be an int

    for (int i = 0; i < m_classes; ++i)
    {
        auto rect = new QGraphicsRectItem(this);

        auto pen = s_pen;
        pen.setWidthF(1.0 / m_view->devicePixelRatio());
        rect->setPen(pen);

        rect->setRect(padding, padding + i * rectSize.height(), rectSize.width(), rectSize.height());

        m_rects << rect;
    }

    updateBrushes();
    updateTooltips();

    const auto invRatio = 1.0 / m_view->devicePixelRatio();
    m_frame->setRect(0, 0, rectSize.width() + 2.0 * padding + invRatio,
        rectSize.height() * m_classes + 2.0 * padding + invRatio);
    
    update();
}

void ColorSchemeGraphicsItem::updateVisibility(
    ColorScheme::ColorSchemeTypes typeFilter, 
    int classesFilter)
{
    if (!m_scheme)
        return;
    
    bool isVisible = true;
    isVisible &= typeFilter.testFlag(m_scheme->type());
    isVisible &= m_scheme->minClasses() <= classesFilter && m_scheme->maxClasses() >= classesFilter;
    
    setVisible(isVisible);
}

void ColorSchemeGraphicsItem::updateBrushes()
{
    for (int i = 0; i < m_classes; ++i)
    {
        auto rect(m_rects[i]);

        if (m_scheme)
        {
            auto color = m_scheme->colors(m_classes)[i];
            color = ColorScheme::daltonize(color, m_deficiency);

            rect->setBrush(RGBABrush(color));
        }
        else
            rect->setBrush(Qt::NoBrush);
    }
}

void ColorSchemeGraphicsItem::updateTooltips()
{
    if (!m_scheme)
    {
        setToolTip("");
        return;
    }

    if (!m_detailedTooltip)
    {
        setToolTip(QString("%1 (%2 to %3 classes)").arg(m_scheme->identifier()).arg(m_scheme->minClasses()).arg(m_scheme->maxClasses()));
        return;
    }
    
    const auto tooltip = QString("%1 - %2").arg(m_scheme->identifier());
    for (int i = 0; i < m_classes; ++i)
    {
        //QColor color = m_scheme->colors(m_classes)[i];
        m_rects[i]->setToolTip(tooltip.arg(m_scheme->colors(m_classes)[i].name(QColor::HexArgb)));
    }
}

QRectF ColorSchemeGraphicsItem::boundingRect() const
{
    return m_frame->rect();
}

void ColorSchemeGraphicsItem::paint(
    QPainter * painter, 
    const QStyleOptionGraphicsItem * option, 
    QWidget * widget)
{
}

void ColorSchemeGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    m_frame->setBrush(s_hoveredBrush);
    event->accept();

    update();
}

void ColorSchemeGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
    m_frame->setBrush(isSelected() ? s_selectedBrush : Qt::NoBrush);
    event->accept();

    update();
}

void ColorSchemeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    setSelected(true, true);
}

} // namespace widgetzeug
