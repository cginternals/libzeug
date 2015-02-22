
#include "ColorSchemeGraphicsItemGroup.h"

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

ColorSchemeGraphicsItemGroup::~ColorSchemeGraphicsItemGroup()
{
}

QRectF ColorSchemeGraphicsItemGroup::boundingRect() const
{
    return QRectF();
}

void ColorSchemeGraphicsItemGroup::paint(QPainter * painter, 
    const QStyleOptionGraphicsItem * option, QWidget * widget)
{
}

void ColorSchemeGraphicsItemGroup::addScheme(const ColorScheme * scheme)
{
    if (m_itemsByScheme.contains(scheme))
        return;

    auto item = new ColorSchemeGraphicsItem(*scheme);
    item->setY(-item->boundingRect().height());

    item->setParentItem(this);
    connect(item, &ColorSchemeGraphicsItem::selected
        , this, &ColorSchemeGraphicsItemGroup::onSelected);

    //m_schemes.append(scheme);
    m_itemsByScheme.insert(scheme, item);

    m_types |= scheme->type();
    m_minClasses = qMin(m_minClasses, scheme->minClasses());
    m_maxClasses = qMax(m_maxClasses, scheme->maxClasses());
}

bool ColorSchemeGraphicsItemGroup::hasScheme(const ColorScheme * scheme) const
{
    return m_itemsByScheme.contains(scheme);
}

ColorSchemeGraphicsItem * ColorSchemeGraphicsItemGroup::schemeGraphicsItem(const ColorScheme * scheme) const
{
    return m_itemsByScheme.value(scheme);
}

bool ColorSchemeGraphicsItemGroup::setSelected(const ColorScheme * scheme)
{
    if (!m_itemsByScheme.contains(scheme))
        return false;

    auto item = m_itemsByScheme.value(scheme);
    item->setSelected(true);

    return true;
}

QList<ColorSchemeGraphicsItem *> ColorSchemeGraphicsItemGroup::items() const
{
    return m_itemsByScheme.values();
}

void ColorSchemeGraphicsItemGroup::update(
    ColorScheme::ColorSchemeTypes typeFilter, 
    uint classesFilter)
{
    updateVisibility(typeFilter, classesFilter);

    if (!isVisible())
        return;
        
    qreal left = m_label->boundingRect().height();

    for (auto item : m_itemsByScheme.values())
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
    for (auto item : m_itemsByScheme)
        item->updateRects();
}

void ColorSchemeGraphicsItemGroup::onSelected(const ColorScheme & scheme)
{
   emit selected(m_itemsByScheme[&scheme]);
}

void ColorSchemeGraphicsItemGroup::setDeficiency(ColorScheme::ColorVisionDeficiency deficiency)
{
   for (auto item : m_itemsByScheme)
        item->setDeficiency(deficiency);
}

void ColorSchemeGraphicsItemGroup::updateVisibility(
    ColorScheme::ColorSchemeTypes typeFilter, const uint classesFilter)
{
    auto isVisible = true;

   isVisible &= !m_itemsByScheme.keys().isEmpty();
    isVisible &= static_cast<bool>(typeFilter & m_types);
    isVisible &= m_minClasses <= classesFilter && m_maxClasses >= classesFilter;

    setVisible(isVisible);
}

} // namespace widgetzeug
