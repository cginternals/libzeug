#pragma once

#include <QMap>
#include <QStringList>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorScheme.h>
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
    virtual ~ColorSchemeGraphicsView();

    void createGroup(const QString & identifier);

    void insertScheme(const QString & group, const ColorScheme & scheme);

    void setSelected(const ColorScheme * scheme);
    const ColorScheme * selected();

    void setTypeFilter(const ColorScheme::ColorSchemeTypes & types);
    const ColorScheme::ColorSchemeTypes & typeFilter() const;

    void setClassesFilter(uint classes);
    uint classesFilter() const;

    void setDeficiency(ColorScheme::ColorVisionDeficiency deficiency);
    ColorScheme::ColorVisionDeficiency deficiency() const;

    uint minClasses() const;
    uint maxClasses() const;

    void ensureDefaultSelection();

protected:
    virtual void keyPressEvent(QKeyEvent * event);

    void setSelectedItem(ColorSchemeGraphicsItem * item);

signals:
    void selectedChanged(const ColorScheme * scheme);
    
private:
    void update();
    QVector<const ColorScheme *> schemes(bool visible = true) const;

private:
    QStringList m_groups;
    QMap<QString, ColorSchemeGraphicsItemGroup *> m_graphicsItemGroups;

    ColorSchemeGraphicsItem * m_selectedItem;

    ColorScheme::ColorSchemeTypes m_typeFilter;
    ColorScheme::ColorVisionDeficiency m_deficiency;

    int m_classesFilter;

    static const int s_padding;
};

} // namespace widgetzeug
