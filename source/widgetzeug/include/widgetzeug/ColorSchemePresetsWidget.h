#pragma once

#include <QWidget>
#include <QMap>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/ColorVisionDeficiency.h>


class QFile;
class QGraphicsTextItem;
class QGraphicsItemGroup;

class Ui_ColorSchemePresetWidget;


namespace widgetzeug
{

class ColorSchemePresets;

class ColorSchemeGraphicsItem;
class ColorSchemeGraphicsView;

/** @brief Widget that shows a list of predefined color schemes.
 *
 *  The color schemes can be inserted in named groups, and be filtered by type
 *  and number of data classes. Neither has an effect on the selected color 
 *  scheme. Further, a simulated color vision deficiency preview can be applied,
 *  aiding the selection process.
 */
class WIDGETZEUG_API ColorSchemePresetsWidget : public QWidget
{
    Q_OBJECT

public:
    ColorSchemePresetsWidget(QWidget * parent = nullptr);
    ColorSchemePresetsWidget(const ColorSchemePresets & presets, QWidget * parent = nullptr);
    virtual ~ColorSchemePresetsWidget();

    /** Clears all previous groups and schemes and reinitializes with schems from given presets.
     */
    void setPresets(const ColorSchemePresets & presets);

    void createGroup(const QString & identifier);
    void insertScheme(const QString & group, const ColorScheme & scheme);

    void setSelected(const QString & identifier);
    void setSelected(const ColorScheme & scheme);
    const ColorScheme * selected();

    void setTypeFilter(const ColorScheme::ColorSchemeTypes & types);
    ColorScheme::ColorSchemeTypes typeFilter() const;

    void setClassesFilter(uint classes);
    uint classesFilter() const;

    /** Enables a color vision deficiency simulation, visually aiding the 
     *  selection process. Setting this filter has no implications on the 
     *  colors of the selected color scheme.
     */
    void setDeficiency(ColorVisionDeficiency deficiency);
    ColorVisionDeficiency deficiency() const;

signals:
    void selectedChanged(const ColorScheme * scheme);

protected slots:
    void on_sequentialCheckBox_stateChanged (int state);
    void on_divergingCheckBox_stateChanged  (int state);
    void on_qualitativeCheckBox_stateChanged(int state);
    void on_classesSpinBox_valueChanged     (int value);

    void on_deficiencyComboBox_currentIndexChanged(int index);

protected:
    void initialize();

protected:
    using deficiency_type = std::underlying_type<ColorVisionDeficiency>::type;

    Ui_ColorSchemePresetWidget * m_ui;
};

} // namespace widgetzeug
