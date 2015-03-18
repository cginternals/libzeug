#pragma once

#include <QMap>
#include <QStringList>

#include <widgetzeug/widgetzeug_api.h>

#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/ColorVisionDeficiency.h>
#include <widgetzeug/DpiAwareGraphicsView.h>


class QFile;

namespace widgetzeug
{

class ColorSchemeGraphicsItem;
class ColorSchemeGraphicsItemGroup;


class ColorSchemeGraphicsView : public DpiAwareGraphicsView
{
    Q_OBJECT

public:
    ColorSchemeGraphicsView(QWidget * parent = nullptr);
    virtual ~ColorSchemeGraphicsView() = default;

    void clear();

    void createGroup(const QString & identifier);

    void insertScheme(const QString & group, const ColorScheme * scheme);

    void setSelected(const QString & scheme);
    void setSelected(const ColorScheme * scheme);
    const ColorScheme * selected();

    void setTypeFilter(const ColorScheme::ColorSchemeTypes & types);
    const ColorScheme::ColorSchemeTypes & typeFilter() const;

    void setClassesFilter(uint classes);
    uint classesFilter() const;

    void setDeficiency(ColorVisionDeficiency deficiency);
    ColorVisionDeficiency deficiency() const;

    uint minClasses() const;
    uint maxClasses() const;

    void setSelectedItem(ColorSchemeGraphicsItem * item);

	void update();

signals:
    void selectedChanged(const ColorScheme * scheme);

protected:
    virtual void keyPressEvent(QKeyEvent * event);

protected:
    QStringList m_groups;
    QMap<QString, ColorSchemeGraphicsItemGroup *> m_graphicsItemGroups;

    ColorSchemeGraphicsItem * m_selectedItem;

    ColorScheme::ColorSchemeTypes m_typeFilter;
    ColorVisionDeficiency m_deficiency;

    uint m_classesFilter;
    uint m_minClasses;
    uint m_maxClasses;

    static const int s_padding;
};

} // namespace widgetzeug
