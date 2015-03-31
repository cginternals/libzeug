
#include "ColorSchemeGraphicsView.h"

#include <assert.h>

#include <QKeyEvent>

#include <widgetzeug/ColorScheme.h>

#include "ColorSchemeGraphicsItem.h"
#include "ColorSchemeGraphicsItemGroup.h"


namespace widgetzeug
{

const int ColorSchemeGraphicsView::s_padding(1);


ColorSchemeGraphicsView::ColorSchemeGraphicsView(QWidget * parent)
:   DpiAwareGraphicsView(parent)
, m_selectedItem(nullptr)
, m_typeFilter(ColorScheme::Diverging | ColorScheme::Qualitative | ColorScheme::Sequential | ColorScheme::Unknown)
, m_deficiency(ColorVisionDeficiency::None)
, m_classesFilter(0)
{
    setScene(new QGraphicsScene());
    clear();

    connect(this, &DpiAwareGraphicsView::dpiChanged, this, &ColorSchemeGraphicsView::update);
}

void ColorSchemeGraphicsView::clear()
{
    m_selectedItem = nullptr;

    m_groups.clear();
    m_graphicsItemGroups.clear();

    m_minClasses = static_cast<uint>(-1);
    m_maxClasses = 0;

    scene()->clear();
    scene()->update();
}

void ColorSchemeGraphicsView::createGroup(const QString & identifier)
{
    if (m_groups.contains(identifier))
        return;

    auto group = new ColorSchemeGraphicsItemGroup(identifier, this);
    connect(group, &ColorSchemeGraphicsItemGroup::selected, 
            this, &ColorSchemeGraphicsView::setSelectedItem);

    scene()->addItem(group);

    m_groups.append(identifier);
    m_graphicsItemGroups.insert(identifier, group);

    update();
}

void ColorSchemeGraphicsView::insertScheme(const QString & group, const ColorScheme * scheme)
{
    assert(scheme);

    createGroup(group);

    m_minClasses = qMin(scheme->minClasses(), m_minClasses);
    m_maxClasses = qMax(scheme->maxClasses(), m_maxClasses);

    assert(m_graphicsItemGroups.value(group) != nullptr);

    m_graphicsItemGroups.value(group)->addScheme(scheme);

    update();
}

void ColorSchemeGraphicsView::update()
{
    auto left = 0;

    for (const auto & identifier : m_groups)
    {
        auto group = m_graphicsItemGroups.value(identifier);
        
        group->updateRects();
        group->update(m_typeFilter, m_classesFilter);

        if (!group->isVisible())
            continue;

        group->setX(left);
        left += group->childrenBoundingRect().width();
    }
    
    if (m_selectedItem && !m_selectedItem->isVisible())
        setSelectedItem(nullptr);

    auto r = scene()->itemsBoundingRect();

    r.setWidth(left);
    r.adjust(0, 0, +5 * dpiBasedScale(), 0);

    scene()->setSceneRect(r);
    setFixedHeight(r.height() + 32 * dpiBasedScale());
}

void ColorSchemeGraphicsView::keyPressEvent(QKeyEvent * event)
{
    if (!m_selectedItem && event->key() != Qt::Key_Right && event->key() != Qt::Key_Left)
    {
        QGraphicsView::keyPressEvent(event);
        return;
    }

    QList<ColorSchemeGraphicsItem*> items;

    for (const auto & identifier : m_groups)
    {
        auto group = m_graphicsItemGroups.value(identifier);
        for (auto item : group->items())
            if (item->isVisible())
                items << item;
    }

    assert(items.contains(m_selectedItem));

    auto index = items.indexOf(m_selectedItem);

    switch (event->key())
    {
    case Qt::Key_Left:
        index = index - 1 < 0 ? items.count() - 1 : index - 1;
        break;

    case Qt::Key_Right:
        index = index + 1 < items.count() ? index + 1 : 0;
        break;

    default:
        break;
    }
    setSelectedItem(items[index]);
}

void ColorSchemeGraphicsView::setSelected(const QString & scheme)
{
    for (const auto & identifier : m_groups)
    {
        auto group = m_graphicsItemGroups.value(identifier);
        for (auto item : group->items())
        {
            if (!item->isVisible() || item->scheme().identifier() != scheme)
                continue;

            setSelectedItem(group->graphicsItem(&item->scheme()));
            return;
        }
    }
    setSelectedItem(nullptr);
}


void ColorSchemeGraphicsView::setSelected(const ColorScheme * scheme)
{
    assert(scheme);

    for (ColorSchemeGraphicsItemGroup * group : m_graphicsItemGroups)
    {
        if (!group->hasScheme(scheme))
            continue;

        setSelectedItem(group->graphicsItem(scheme));
        return;
    }
    setSelectedItem(nullptr);
}

void ColorSchemeGraphicsView::setSelectedItem(ColorSchemeGraphicsItem * item)
{
    if (m_selectedItem)
        m_selectedItem->setSelected(false);

    m_selectedItem = item;
    if (m_selectedItem)
    {
        m_selectedItem->setSelected(true);
        
        const auto xMargin = m_selectedItem->rectSize().width()
        + m_selectedItem->margin()
        + m_selectedItem->padding() + 2;
        ensureVisible(m_selectedItem, xMargin * dpiBasedScale(), 0);
    }
    
    emit selectedChanged(item ? &(item->scheme()) : nullptr);
}

const ColorScheme * ColorSchemeGraphicsView::selected()
{
    return m_selectedItem ? &(m_selectedItem->scheme()) : nullptr;
}

void ColorSchemeGraphicsView::setTypeFilter(const ColorScheme::ColorSchemeTypes & types)
{
    if (m_typeFilter == types)
        return;

    m_typeFilter = types;
    update();
}

const ColorScheme::ColorSchemeTypes & ColorSchemeGraphicsView::typeFilter() const
{
    return m_typeFilter;
}

void ColorSchemeGraphicsView::setClassesFilter(uint classes)
{
    if (m_classesFilter == classes)
        return;

    m_classesFilter = classes;
    update();
}

uint ColorSchemeGraphicsView::classesFilter() const
{
    return m_classesFilter;
}

void ColorSchemeGraphicsView::setDeficiency(const ColorVisionDeficiency deficiency)
{
    m_deficiency = deficiency;

    for (ColorSchemeGraphicsItemGroup * group : m_graphicsItemGroups)
        group->setDeficiency(deficiency);

    update();
}

ColorVisionDeficiency ColorSchemeGraphicsView::deficiency() const
{
    return m_deficiency;
}

uint ColorSchemeGraphicsView::minClasses() const
{
    return m_minClasses;
}

uint ColorSchemeGraphicsView::maxClasses() const
{
    return m_maxClasses;
}

} // namespace widgetzeug
