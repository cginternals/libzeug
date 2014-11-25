#include <propertyguizeug/dpi_util.h>

#include <cassert>

#include <QPaintDevice>

namespace propertyguizeug
{

qreal dpiBasedScale(const QPaintDevice & device)
{
#ifdef Q_OS_MAC
    return 1.0;
#else
    assert(device.logicalDpiX() == device.logicalDpiY());
    static const auto standardDpi = 96.0;
    
    const dpi = device.logicalDpiX();
    return dpi / standardDpi;
#endif
}

} // namespace propertyguizeug
