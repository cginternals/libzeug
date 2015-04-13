#pragma once

#include <QMap>
#include <QVector>
#include <QFlags>
#include <QColor>

class QJsonObject;

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorVisionDeficiency.h>


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
* Example for such a JsonObject:
* \code{.json}
* ...
*     "OrRd": {"3": ["(254,232,200)", "(253,187,132)", "(227, 74, 51)"], "4": ["(254,240,217)", "(253,204,138)", "(252,141, 89)", "(215, 48, 31)"], ..., "type": "Sequential"} ,
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
    ,   Sequential  = 1
    ,   Diverging   = 2
    ,   Qualitative = 4
    };
    Q_DECLARE_FLAGS(ColorSchemeTypes, ColorSchemeType)
    static const QMap<ColorSchemeType, QString> s_types;

    static const QMap<ColorVisionDeficiency, QString> s_deficiencies;

public:
    ColorScheme();
    ColorScheme(const QString & identifier);
    ColorScheme(const QString & identifier, ColorSchemeType type);
    ColorScheme(const QString & identifier, QJsonObject scheme);

    virtual ~ColorScheme() = default;

    bool operator==(const ColorScheme & scheme) const;

    void setIdentifier(const QString & identifier);
    const QString & identifier() const;

    void setColors(const QVector<QColor> & colors);
    const QVector<QColor> colors(uint classes) const;

    void setType(ColorSchemeType type);
    ColorSchemeType type() const;

    uint minClasses() const;
    uint maxClasses() const;

protected:
    QString m_identifier;
    ColorSchemeType m_type;

    QMap<uint, QVector<QColor>> m_colorsByClass;
};

} // namespace widgetzeug

//bool WIDGETZEUG_API operator ==(const widgetzeug::ColorScheme & a, const widgetzeug::ColorScheme & b);
