#pragma once

#include <QtGlobal>

#include <propertyguizeug/propertyguizeug_api.h>

class QPaintDevice;
class QWidget;

namespace propertyguizeug
{

PROPERTYGUIZEUG_API qreal dpiBasedScale(const QWidget & device);

} // namespace propertyguizeug
