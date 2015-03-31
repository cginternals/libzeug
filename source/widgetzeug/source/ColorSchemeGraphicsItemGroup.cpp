
#include "ColorSchemeGraphicsItemGroup.h"

#include <cassert>
#include <functional>
#include <limits>

#include <QGraphicsTextItem>
#include <QString>

#include <widgetzeug/DpiAwareGraphicsView.h>

#include "ColorSchemeGraphicsItem.h"


namespace widgetzeug
{

ColorSchemeGraphicsItemGroup::ColorSchemeGraphicsItemGroup(
    const QString & identifier,
    const DpiAwareGraphicsView * view)
: m_label{ new QGraphicsTextItem(identifier, this) }
, m_view{ view }
, m_minClasses{ std::numeric_limits<int>::max() }
, m_maxClasses{ 0 }
{
    m_label->setRotation(-90);
    m_label->setOpacity(0.5);
}

QRectF ColorSchemeGraphicsItemGroup::boundingRect() const
{
    return QRect();
}

void ColorSchemeGraphicsItemGroup::paint(QPainter * painter, 
    const QStyleOptionGraphicsItem * option, QWidget * widget)
{
}

void ColorSchemeGraphicsItemGroup::addScheme(const ColorScheme * scheme)
{
    if (!scheme || m_itemsByScheme.contains(scheme))
        return;

    auto item = new ColorSchemeGraphicsItem(*scheme);
    item->setY(-item->boundingRect().height());

    item->setParentItem(this);
    connect(item, &ColorSchemeGraphicsItem::selected
        , this, &ColorSchemeGraphicsItemGroup::selected);

    m_itemsByScheme.insert(scheme, item);

    auto i = 0; // use insertion sort ...
    while (i < m_items.count() && m_items[i]->scheme().identifier().compare(scheme->identifier(), Qt::CaseInsensitive) < 0)
        ++i;
    m_items.insert(i, item);

    m_types |= scheme->type();
    m_minClasses = qMin(m_minClasses, scheme->minClasses());
    m_maxClasses = qMax(m_maxClasses, scheme->maxClasses());
}

bool ColorSchemeGraphicsItemGroup::hasScheme(const ColorScheme * scheme) const
{
    if (!scheme)
        return false;

    return m_itemsByScheme.contains(scheme);
}

ColorSchemeGraphicsItem * ColorSchemeGraphicsItemGroup::graphicsItem(const ColorScheme * scheme) const
{
    if (!hasScheme(scheme))
        return nullptr;

    return m_itemsByScheme.value(scheme);
}

bool ColorSchemeGraphicsItemGroup::setSelected(const ColorScheme * scheme)
{
    if (!scheme)
    {
        for (auto item : m_items)
            item->setSelected(false);

        return true;
    }

    if (!m_itemsByScheme.contains(scheme))
        return false;

    auto item = m_itemsByScheme.value(scheme);

    assert(item != nullptr);

    item->setSelected(true);

    return true;
}

QList<ColorSchemeGraphicsItem *> ColorSchemeGraphicsItemGroup::items() const
{
    return m_items;
}

void ColorSchemeGraphicsItemGroup::update(
    ColorScheme::ColorSchemeTypes typeFilter, 
    uint classesFilter)
{
    setVisibility(typeFilter, classesFilter);

    if (!isVisible())
        return;
        
    qreal left = m_label->boundingRect().height();

    for (auto item : m_items)
    {
        item->updateVisibility(typeFilter, classesFilter);

        if (!item->isVisible())
            continue;

        item->setX(left);

        left += 1.0 / m_view->devicePixelRatio() + item->boundingRect().width();
    }
}

void ColorSchemeGraphicsItemGroup::updateRects()
{
    for (auto item : m_items)
        item->updateRects();
}

void ColorSchemeGraphicsItemGroup::setDeficiency(const ColorVisionDeficiency deficiency)
{
    for (auto item : m_items)
        item->setDeficiency(deficiency);
}


void ColorSchemeGraphicsItemGroup::setVisibility(
    ColorScheme::ColorSchemeTypes typeFilter, const uint classesFilter)
{
    auto isVisible = true;

    isVisible &= !m_items.isEmpty();
    isVisible &= static_cast<bool>(typeFilter & m_types);
    isVisible &= m_minClasses <= classesFilter && m_maxClasses >= classesFilter;

    setVisible(isVisible);
}

} // namespace widgetzeug
