#pragma once

#include <QColor>

#include <widgetzeug/widgetzeug_api.h>


namespace widgetzeug
{

enum class ColorVisionDeficiency
{
    None
,   Protanope   // reds are greatly reduced   (1% men)
,   Deuteranope // greens are greatly reduced (1% men)
,   Tritanope   // blues are greatly reduced  (0.003% population)
,   Grayscale   // not an actual deficiency, but useful
};

/** \brief Allows simulating color vision deficiencies.
*
* Allows simulating color vision deficiencies, to aid selection process and/or provide
* simulated preview of mappings appropriate for color-blind viewers .
*/
WIDGETZEUG_API QColor daltonize(const QColor & color, ColorVisionDeficiency deficiency);

} // namespace widgetzeug
