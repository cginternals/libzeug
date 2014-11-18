#pragma once

#include <QWidget>
#include <QMap>
#include <QStringList>
#include <QScopedPointer>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorScheme.h>

class QFile;
class QGraphicsTextItem;
class QGraphicsItemGroup;

class Ui_ColorSchemePresetWidget;

namespace widgetzeug
{

class ColorSchemeGraphicsItem;
class ColorSchemeGraphicsView;

/** \brief Widget that shows a list of predefined color schemes.
*
* The color schemes can be inserted in named groups, and be filtered by type 
* and number of data classes. Neither has an effect on the selected color 
* scheme. Further, a simulated color vision deficiency preview can be applied,
* aiding the selection process.
*
* The complete widget can be retrieved from a Json format (based on the Json 
* provided by the ColorBrewer 2.0: \see http://colorbrewer2.org 
* © Cynthia Brewer, Mark Harrower and The Pennsylvania State University)
*
* Json example (colorbrewer json format, extended by named categories):
* \code{.json}
* {
*   "sequential\nmulti-hue": {
*     "categorie-index": 0,
*     "OrRd": {"3": ["(254,232,200)", "(253,187,132)", "(227, 74, 51)"], "4": ["(254,240,217)", "(253,204,138)", "(252,141, 89)", "(215, 48, 31)"], ..., "type": "seq"} ,
*     "PuBu": {"3": ["(236,231,242)", "(166,189,219)", "( 43,140,190)"], "4": ["(241,238,246)", "(189,201,225)", "(116,169,207)", "(  5,112,176)"], ..., "type": "seq"} ,
*     ...
*   },
*   "sequential\nsingle-hue": {
*     "categorie-index": 1,
*     "Oranges":  {"3": ["(254,230,206)", "(253,174,107)", "(230, 85, 13)"], "4": ["(254,237,222)", "(253,190,133)", "(253,141,60)", "(217,71,1)"], ..., "type": "seq"} ,
*     ...
*   },
*   ...
* }
* \endcode
*/
class WIDGETZEUG_API ColorSchemePresetsWidget : public QWidget
{
    Q_OBJECT

public:
    static ColorSchemePresetsWidget * fromJson(QFile & file, QWidget * parent = nullptr);

public:
    ColorSchemePresetsWidget(QWidget * parent = nullptr);
    virtual ~ColorSchemePresetsWidget();

    void createGroup(const QString & identifier);
    void insertScheme(const QString & group, ColorScheme * scheme);

    void setSelected(ColorScheme * scheme);
    ColorScheme * selected();

    void setTypeFilter(const ColorScheme::ColorSchemeTypes & types);
    const ColorScheme::ColorSchemeTypes & typeFilter() const;

    void setClassesFilter(int classes);
    int classesFilter() const;

    /** Enables a color vision deficiency simulation, visually aiding the 
     * selection process. Setting this filter has no implications on the 
     * colors of the selected color scheme.
     */
    void setDeficiency(ColorScheme::ColorVisionDeficiency deficiency);
    ColorScheme::ColorVisionDeficiency deficiency() const;

	void ensureDefaultSelection();

signals:
    void selectedChanged(ColorScheme * scheme);
    
protected slots:
    void on_sequentialCheckBox_stateChanged (int state);
    void on_divergingCheckBox_stateChanged  (int state);
    void on_qualitativeCheckBox_stateChanged(int state);
    void on_classesSpinBox_valueChanged     (int value);

    void on_deficiencyComboBox_currentIndexChanged(int index);

protected:
    const QScopedPointer<Ui_ColorSchemePresetWidget> m_ui;
};

} // namespace widgetzeug
