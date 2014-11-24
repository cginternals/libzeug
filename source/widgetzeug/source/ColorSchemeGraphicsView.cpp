
#include "ColorSchemeGraphicsView.h"

#include <cassert>

#include <QDebug>
#include <QMouseEvent>

#include "ColorSchemeGraphicsItem.h"
#include "ColorSchemeGraphicsItemGroup.h"


namespace widgetzeug
{

const int ColorSchemeGraphicsView::s_padding(1);

ColorSchemeGraphicsView::ColorSchemeGraphicsView(QWidget * parent)
:   DpiAwareGraphicsView(parent)
,   m_selectedItem(nullptr)
,   m_typeFilter(ColorScheme::Diverging | ColorScheme::Qualitative | ColorScheme::Sequential | ColorScheme::Unknown)
,   m_deficiency(ColorScheme::None)
,   m_classesFilter(0)
{
    setScene(new QGraphicsScene());

    connect(this, &DpiAwareGraphicsView::dpiChanged,
            this, &ColorSchemeGraphicsView::update);
}

ColorSchemeGraphicsView::~ColorSchemeGraphicsView()
{
}

void ColorSchemeGraphicsView::createGroup(const QString & identifier)
{
    if (m_groups.contains(identifier))
        return;

    ColorSchemeGraphicsItemGroup * group = new ColorSchemeGraphicsItemGroup(identifier, this);
    connect(group, &ColorSchemeGraphicsItemGroup::selected, 
            this, &ColorSchemeGraphicsView::setSelectedItem);

    scene()->addItem(group);

    m_groups.append(identifier);
    m_graphicsItemGroups.insert(identifier, group);
}

void ColorSchemeGraphicsView::insertScheme(const QString & group, ColorScheme * scheme)
{
    if (nullptr == scheme)
        return;

    createGroup(group);

    m_graphicsItemGroups.value(group)->addScheme(scheme);
}

void ColorSchemeGraphicsView::update()
{
    int left = 0;

    for (const QString & identifier : m_groups)
    {
        ColorSchemeGraphicsItemGroup * group = m_graphicsItemGroups.value(identifier);
        
        group->updateRects();
        group->update(m_typeFilter, m_classesFilter);

        if (!group->isVisible())
            continue;

        group->setX(left);
        left += group->childrenBoundingRect().width();
    }
    
    if (m_selectedItem && !m_selectedItem->isVisible())
        setSelectedItem(nullptr);

    QRectF r(scene()->itemsBoundingRect());

    r.setWidth(left);
    r.adjust(0, 0, +5 * dpiBasedScale(), 0);

    scene()->setSceneRect(r);
    setFixedHeight(r.height() + 32 * dpiBasedScale());
}

void ColorSchemeGraphicsView::keyPressEvent(QKeyEvent * event)
{
    int offset = 0;
    
    switch (event->key()) 
    {
        case Qt::Key_Right:
            offset = 1;
            break;
        case Qt::Key_Left:
            offset = -1;
            break;
            
        default:
            break;
    }
    
    if (!offset)
        return;
        
    if (!m_selectedItem)
    {
        setSelected(visibleSchemes().first());
        return;
    }

    QList<ColorScheme *> schemes = this->visibleSchemes();
    int index = schemes.indexOf(m_selectedItem->scheme());
    index += offset;
    if (index < 0)
        index = schemes.count() - 1;
    if (index >= schemes.count())
        index = 0;
    setSelected(schemes.at(index));
    ensureVisible(m_selectedItem, 20 * dpiBasedScale(), 0);
}

void ColorSchemeGraphicsView::setSelected(ColorScheme * scheme)
{
    if (!scheme)
    {
        setSelectedItem(nullptr);
        return;
    }

    for (ColorSchemeGraphicsItemGroup * group : m_graphicsItemGroups)
    {
        if (group->hasScheme(scheme))
        {
            ColorSchemeGraphicsItem * item = group->schemeGraphicsItem(scheme);
            item->setSelected(true);
            setSelectedItem(group->schemeGraphicsItem(scheme));
            break;
        }
    }
}

void ColorSchemeGraphicsView::setSelectedItem(ColorSchemeGraphicsItem * item)
{
    if (m_selectedItem)
        m_selectedItem->setSelected(false);
            
    m_selectedItem = item;
    
    emit selectedChanged(item ? item->scheme() : nullptr);
}

ColorScheme * ColorSchemeGraphicsView::selected()
{
    return m_selectedItem ? m_selectedItem->scheme() : nullptr;
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

void ColorSchemeGraphicsView::setClassesFilter(int classes)
{
    if (m_classesFilter == classes)
        return;

    m_classesFilter = classes;
    update();
}

int ColorSchemeGraphicsView::classesFilter() const
{
    return m_classesFilter;
}

void ColorSchemeGraphicsView::setDeficiency(ColorScheme::ColorVisionDeficiency deficiency)
{
    m_deficiency = deficiency;

    for (ColorSchemeGraphicsItemGroup * group : m_graphicsItemGroups)
        group->setDeficiency(deficiency);

    update();
}

ColorScheme::ColorVisionDeficiency ColorSchemeGraphicsView::deficiency() const
{
    return m_deficiency;
}

QList<ColorScheme *> ColorSchemeGraphicsView::visibleSchemes() const
{
    QList<ColorScheme *> schemes;
    for (const QString & identifier : m_groups)
    {
        ColorSchemeGraphicsItemGroup * group = m_graphicsItemGroups.value(identifier);
        for (ColorSchemeGraphicsItem * item : group->schemeGraphicsItems())
            if (item->isVisible())
                schemes << item->scheme();
    }
    return schemes;
}

void ColorSchemeGraphicsView::ensureDefaultSelection()
{
	if (m_selectedItem == nullptr)
		setSelected(!visibleSchemes().isEmpty() ? visibleSchemes().first() : nullptr);
}

} // namespace widgetzeug
