#pragma once

#include <QMap>
#include <QList>
#include <QFlags>
#include <QColor>

class QJsonObject;

#include <widgetzeug/widgetzeug_api.h>

namespace widgetzeug
{

/** \brief A color scheme is a set of consecutive color sequences for a color mapping.
*
* A color scheme is an isntantiated color mapping for various numbers of data 
* classes, for each of which, an individual color sequence is provided. E.g., 
* the 3 colors provided for 3 data classes might be similar but not equal to 
* the colors provided for 4 data classes (especially for qualitative colors).
*
* Color schemes provide an identifier as well as its color mapping type based
* on the nature of the mapped data. 
*
* A color scheme can either be specified programmatically or by a JsonObject.
* Example for such an JsonObject:
* \code{.json}
* ...
*     "OrRd": {"3": ["(254,232,200)", "(253,187,132)", "(227, 74, 51)"], "4": ["(254,240,217)", "(253,204,138)", "(252,141, 89)", "(215, 48, 31)"], ..., "type": "seq"} ,
* ...
* \endcode
* }
* 
* Further, the color scheme allows simulating color vision deficiencies, to aid
* selection process of mappings appropriate for color-blind viewers.
*
* The classes structure was initially influenced by and the provided json data
* based on the ColorBrewer 2.0: \see http://colorbrewer2.org 
* ? Cynthia Brewer, Mark Harrower and The Pennsylvania State University
*/
class WIDGETZEUG_API ColorScheme
{
public:
    enum ColorSchemeType
    {
        Unknown     = 0
    ,   Sequential  = 1 // "seq"
    ,   Diverging   = 2 // "div"
    ,   Qualitative = 4 // "qual"
    };
    Q_DECLARE_FLAGS(ColorSchemeTypes, ColorSchemeType)

    enum ColorVisionDeficiency
    {
        None
    ,   Protanope   // reds are greatly reduced   (1% men)
    ,   Deuteranope // greens are greatly reduced (1% men)
    ,   Tritanope   // blues are greatly reduced  (0.003% population)
    ,   Grayscale   // not an actual deficiency, but useful
    };

    static ColorScheme * fromJson(const QString & identifier, const QJsonObject & object);

    static QColor daltonize(const QColor & color, ColorVisionDeficiency deficiency);

public:
    ColorScheme();
    ColorScheme(const QString & identifier);
    ColorScheme(const QString & identifier, ColorSchemeType type);

    virtual ~ColorScheme();

    void setIdentifier(const QString & identifier);
    const QString & identifier() const;

    void setColors(const QList<QColor> & colors);
    const QList<QColor> colors(int classes) const;

    void setType(ColorSchemeType type);
    ColorSchemeType type() const;

    int minClasses() const;
    int maxClasses() const;

protected:
    QString m_identifier;
    ColorSchemeType m_type;

    QMap<int, QList<QColor>> m_colorsByClass;
};

} // namespace widgetzeug

