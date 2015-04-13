
#include "ColorSchemeGraphicsItem.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>
#include <QPainter>
#include <QApplication>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QToolTip>

#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/DpiAware.h>
#include <widgetzeug/RGBABrush.hpp>


namespace widgetzeug
{

ColorSchemeGraphicsItem::ColorSchemeGraphicsItem(
    const ColorScheme & scheme, QGraphicsItem * parent) 
:   QGraphicsObject(parent)
,   m_scheme{ scheme }
,   m_deficiency{ ColorVisionDeficiency::None }
,   m_frame{ new QGraphicsRectItem(this) }
,   m_rectSize{ 17.0, 17.0 }
,   m_margin{ 3.0 } 
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

const ColorScheme & ColorSchemeGraphicsItem::scheme() const
{
    return m_scheme;
}

void ColorSchemeGraphicsItem::setClasses(const uint classes)
{
    m_classes = qBound<uint>(m_scheme.minClasses(), classes, m_scheme.maxClasses());

    updateRects();
}

int ColorSchemeGraphicsItem::classes() const
{
    return m_classes;
}

void ColorSchemeGraphicsItem::setDeficiency(const ColorVisionDeficiency deficiency)
{
    if (deficiency == m_deficiency)
        return;

    m_deficiency = deficiency;
    updateBrushes();
}

ColorVisionDeficiency ColorSchemeGraphicsItem::deficiency() const
{
    return m_deficiency;
}

void ColorSchemeGraphicsItem::setMargin(const qreal margin)
{
    if (margin == m_margin)
        return;

    m_margin = margin;
    updateRects();
}

qreal ColorSchemeGraphicsItem::margin() const
{
    return m_margin;
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

void ColorSchemeGraphicsItem::setSelected(const bool status, const bool signal)
{
    if (status == m_selected)
        return;

    m_selected = status;
    m_frame->setBrush(m_selected ? QPalette().highlight() : Qt::NoBrush);

    if (status && signal)
        emit selected(this);
        
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

    const auto parent = dynamic_cast<QWidget*>(parentWidget());
    const auto dpiScale = DpiAware::dpiBasedScale(parent);
    const auto invRatio = 1.0 / DpiAware::devicePixelRatio(parent);

    const QSize rectSize = m_rectSize.toSize() * dpiScale;
    const int margin  = m_margin * dpiScale; // this is required to be an int

    auto pen = QPen(QPalette().dark().color());
    pen.setWidthF(invRatio);

    for (uint i = 0; i < m_classes; ++i)
    {
        auto rect = new QGraphicsRectItem(this);

        rect->setPen(pen);

        rect->setRect(margin, margin + i * (rectSize.height() + m_padding), rectSize.width(), rectSize.height());
        m_rects << rect;
    }

    updateBrushes();
    updateTooltips();

    m_frame->setRect(0, 0, rectSize.width() + 2.0 * margin + invRatio,
        rectSize.height() * m_classes + m_padding * (m_classes - 1) + 2.0 * margin + invRatio);  
    
    update();
}

void ColorSchemeGraphicsItem::updateVisibility(
    ColorScheme::ColorSchemeTypes typeFilter, 
    uint classesFilter)
{
    bool isVisible = true;
    isVisible &= typeFilter.testFlag(m_scheme.type());
    isVisible &= m_scheme.minClasses() <= classesFilter 
        && m_scheme.maxClasses() >= classesFilter;

    setVisible(isVisible);
}

void ColorSchemeGraphicsItem::updateBrushes()
{
    const auto parent = dynamic_cast<QWidget*>(parentWidget());
    const auto penWidthF = 1.0 / DpiAware::devicePixelRatio(parent);

    for (uint i = 0; i < m_classes; ++i)
    {
        auto rect(m_rects[i]);

        auto color = m_scheme.colors(m_classes)[m_classes - i - 1];
        color = daltonize(color, m_deficiency);

        auto brush = RGBABrush(color);

        // this aligns the brush pattern with the rect (since there is no way to directly set the brush origin similar to a painter)
        brush.setTransform(QTransform::fromTranslate( // who cares ... :P
            m_margin + 1, (m_padding + penWidthF) * static_cast<qreal>(i) + m_margin + 1));

        rect->setBrush(brush);
    }
}

void ColorSchemeGraphicsItem::updateTooltips()
{
    if (!m_detailedTooltip)
    {
        setToolTip(QString("%1 (%2 to %3 classes)").arg(m_scheme.identifier())
            .arg(m_scheme.minClasses()).arg(m_scheme.maxClasses()));
        return;
    }
    
    const auto tooltip = QString("%1 - %2").arg(m_scheme.identifier());
    for (uint i = 0; i < m_classes; ++i)
        m_rects[i]->setToolTip(tooltip.arg(m_scheme.colors(m_classes)[i].name(QColor::HexArgb)));
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
    m_frame->setBrush(QPalette().highlight());
    event->accept();

    update();
}

void ColorSchemeGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
    m_frame->setBrush(isSelected() ? QPalette().highlight() : Qt::NoBrush);
    event->accept();

    update();
}

void ColorSchemeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    setSelected(true, true);
}

} // namespace widgetzeug
