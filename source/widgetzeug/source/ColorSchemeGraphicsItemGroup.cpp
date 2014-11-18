#include <widgetzeug/ColorSchemeGraphicsItemGroup.h>

#include <functional>
#include <limits>

#include <QDebug>
#include <QGraphicsTextItem>
#include <QString>

#include <widgetzeug/DpiAwareGraphicsView.h>

#include <widgetzeug/ColorSchemeGraphicsItem.h>


namespace widgetzeug
{

ColorSchemeGraphicsItemGroup::ColorSchemeGraphicsItemGroup(
    const QString & identifier,
    const DpiAwareGraphicsView * view)
:   m_label(new QGraphicsTextItem(identifier, this))
,   m_view(view)
,   m_minClasses(std::numeric_limits<int>::max())
,   m_maxClasses(0)
{
    m_label->setRotation(-90);
    m_label->setOpacity(0.33);
}

ColorSchemeGraphicsItemGroup::~ColorSchemeGraphicsItemGroup()
{
}

QRectF ColorSchemeGraphicsItemGroup::boundingRect() const
{
    return QRectF();
}

void ColorSchemeGraphicsItemGroup::paint(
    QPainter * painter, 
    const QStyleOptionGraphicsItem * option, 
    QWidget * widget)
{
}

void ColorSchemeGraphicsItemGroup::addScheme(ColorScheme * scheme)
{
    if (nullptr == scheme)
        return;

    if (m_schemeGraphicsItems.contains(scheme))
        return;

    ColorSchemeGraphicsItem * item = new ColorSchemeGraphicsItem(m_view, scheme);
    item->setY(-item->boundingRect().height());
    
    item->setParentItem(this);
    connect(item, &ColorSchemeGraphicsItem::selected,
            this, &ColorSchemeGraphicsItemGroup::onSelected);

    m_schemes.append(scheme);
    m_schemeGraphicsItems.insert(scheme, item);

    m_types |= scheme->type();
    m_minClasses = qMin(m_minClasses, scheme->minClasses());
    m_maxClasses = qMax(m_maxClasses, scheme->maxClasses());
}

bool ColorSchemeGraphicsItemGroup::hasScheme(ColorScheme * scheme) const
{
    return m_schemeGraphicsItems.contains(scheme);
}

ColorSchemeGraphicsItem * ColorSchemeGraphicsItemGroup::schemeGraphicsItem(ColorScheme * scheme) const
{
    return m_schemeGraphicsItems.value(scheme);
}

bool ColorSchemeGraphicsItemGroup::setSelected(ColorScheme * scheme)
{
    if (!m_schemes.contains(scheme))
        return false;
        
    ColorSchemeGraphicsItem * item = m_schemeGraphicsItems.value(scheme);
    item->setSelected(true);
    return true;
}

QList<ColorSchemeGraphicsItem *> ColorSchemeGraphicsItemGroup::schemeGraphicsItems() const
{
    QList<ColorSchemeGraphicsItem *> items;
    for (ColorScheme * scheme : m_schemes)
        items.append(m_schemeGraphicsItems.value(scheme));
    return items;
}

void ColorSchemeGraphicsItemGroup::update(
    ColorScheme::ColorSchemeTypes typeFilter, 
    int classesFilter)
{
    updateVisibility(typeFilter, classesFilter);

    if (!isVisible())
        return;
        
    qreal left = m_label->boundingRect().height();

    for (ColorScheme * scheme : m_schemes)
    {
        ColorSchemeGraphicsItem * item = m_schemeGraphicsItems.value(scheme);

        item->updateVisibility(typeFilter, classesFilter);

        if (!item->isVisible())
            continue;

        item->setX(left);

        left += item->boundingRect().width();
        left += m_view->invDevicePixelRatio();
    }
}

void ColorSchemeGraphicsItemGroup::updateRects()
{
    for (ColorSchemeGraphicsItem * item : m_schemeGraphicsItems)
        item->updateRects();
}

void ColorSchemeGraphicsItemGroup::onSelected(ColorScheme * scheme)
{
    emit selected(m_schemeGraphicsItems[scheme]);
}

void ColorSchemeGraphicsItemGroup::setDeficiency(ColorScheme::ColorVisionDeficiency deficiency)
{
    for (ColorSchemeGraphicsItem * item : m_schemeGraphicsItems)
        item->setDeficiency(deficiency);
}

void ColorSchemeGraphicsItemGroup::updateVisibility(
    ColorScheme::ColorSchemeTypes typeFilter, 
    int classesFilter)
{
    bool isVisible = true;
    isVisible &= !m_schemes.isEmpty();
    isVisible &= bool(typeFilter & m_types);
    isVisible &= m_minClasses <= classesFilter && m_maxClasses >= classesFilter;
    
    setVisible(isVisible);
}

} // namespace widgetzeug
