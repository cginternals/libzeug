#pragma once

#include <widgetzeug/widgetzeug_api.h>


class QString;

namespace widgetzeug
{

class ColorSchemeControlWidget;


/** @brief Support QSettings-based serialization of control widgets.
 */
class WIDGETZEUG_API ControlWidgetSettings
{
public:
    static void store(const QString & key, const ColorSchemeControlWidget & widget);
    static void restore(const QString & key, ColorSchemeControlWidget & widget);
};

} // namespace widgetzeug
