#pragma once

#include <QGraphicsObject>
#include <QList>
#include <QMap>

#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/ColorVisionDeficiency.h>


class QGraphicsTextItem;
class QString;

namespace widgetzeug
{

class ColorSchemeGraphicsItem;
class DpiAwareGraphicsView;


class ColorSchemeGraphicsItemGroup : public QGraphicsObject
{
    Q_OBJECT

public:
    ColorSchemeGraphicsItemGroup(const QString & identifier
        , const DpiAwareGraphicsView * view);

    virtual ~ColorSchemeGraphicsItemGroup() = default;
    
    virtual QRectF boundingRect() const;

    virtual void paint(QPainter * painter
        , const QStyleOptionGraphicsItem * option
        , QWidget * widget = nullptr);

    void addScheme(const ColorScheme * scheme);
    bool hasScheme(const ColorScheme * scheme) const;

    ColorSchemeGraphicsItem * graphicsItem(const ColorScheme * scheme) const;

    bool setSelected(const ColorScheme * scheme);

    QList<ColorSchemeGraphicsItem *> items() const;

    void update(ColorScheme::ColorSchemeTypes typeFilter, uint classesFilter);
    void updateRects();

    void setDeficiency(ColorVisionDeficiency deficiency);

signals:
    void selected(ColorSchemeGraphicsItem * item);

private:
    void setVisibility(ColorScheme::ColorSchemeTypes typeFilter
        , uint classesFilter);

private:
    QGraphicsTextItem * m_label;
    const DpiAwareGraphicsView * m_view;

    QList<ColorSchemeGraphicsItem *> m_items;

    using ItemsByScheme = QMap<const ColorScheme *, ColorSchemeGraphicsItem *>;
    ItemsByScheme m_itemsByScheme;
    
    ColorScheme::ColorSchemeTypes m_types;
    uint m_minClasses;
    uint m_maxClasses;
};

} // namespace widgetzeug
