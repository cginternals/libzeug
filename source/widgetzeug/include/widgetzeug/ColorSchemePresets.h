#pragma once

#include <QVector>

#include <widgetzeug/widgetzeug_api.h>

#include <widgetzeug/ColorScheme.h>


class QJsonObject;


namespace widgetzeug
{

class WIDGETZEUG_API ColorSchemeGroup : public QVector<ColorScheme>
{
public:
    ColorSchemeGroup();
    ColorSchemeGroup(const QString & identifier, const QJsonObject & schemes);

    const QString & identifier() const;

protected:
    QString m_identifier;
};

/**
* A color scheme presets can be retrieved from a Json format (based on the Json
* provided by the ColorBrewer 2.0: \see http://colorbrewer2.org
* © Cynthia Brewer, Mark Harrower and The Pennsylvania State University)
*
* Note: the format is extended by group names and indices that allows for
* better group identification and sequence control. 
*
* Json examples (colorbrewer json format, extended by named categories):
* @code{.json}
* {
*   ...
*   "sequential\nmulti-hue": {
*     "index": 0,
*     "OrRd": {"3": ["(254,232,200)", "(253,187,132)", "(227, 74, 51)"], "4": ["(254,240,217)", "(253,204,138)", "(252,141, 89)", "(215, 48, 31)"], ..., "type": "Sequential"} ,
*     "PuBu": {"3": ["(236,231,242)", "(166,189,219)", "( 43,140,190)"], "4": ["(241,238,246)", "(189,201,225)", "(116,169,207)", "(  5,112,176)"], ..., "type": "Sequential"} ,
*     ...
*   },
*   ...
*   "sequential\nsingle-hue": {
*     "index": 1,
*     "Oranges":  {"3": ["(254,230,206)", "(253,174,107)", "(230, 85, 13)"], "4": ["(254,237,222)", "(253,190,133)", "(253,141,60)", "(217,71,1)"], ..., "type": "Sequential"} ,
*     ...
*   },
*   ...
* }
* @endcode
*/
class WIDGETZEUG_API ColorSchemePresets : public QVector<ColorSchemeGroup>
{
public:
    ColorSchemePresets();
    ColorSchemePresets(const QString & fileName);
    ColorSchemePresets(const QJsonObject & presets);

protected:
    void initialize(const QJsonObject & presets);
};

} // namespace widgetzeug
