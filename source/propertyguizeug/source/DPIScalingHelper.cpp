#include <propertyguizeug/DPIScalingHelper.h>

#include <cassert>

#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QWindow>

namespace propertyguizeug
{

DPIScalingHelper::DPIScalingHelper(QWidget * parent)
:   QObject{parent}
,   m_widget{parent}
,   m_dpiBasedScale{fetchDpiBasedScale()}
,   m_devicePixelRatio{fetchDevicePixelRatio()}
,   m_widgetShown{false}
{
    if (nativeWindow())
        widgetShown();
}

qreal DPIScalingHelper::dpiBasedScale() const
{
    return m_dpiBasedScale;
}

qreal DPIScalingHelper::devicePixelRatio() const
{
    return m_devicePixelRatio;
}

void DPIScalingHelper::widgetShown()
{
    if (m_widgetShown)
        return;

    auto window = nativeWindow();
    assert(window);

    connect(window, &QWindow::screenChanged,
        [this] () 
        {
            auto newDpiBasedScale = dpiBasedScale();
            auto newDevicePixelRatio = devicePixelRatio();

            if (newDpiBasedScale != m_dpiBasedScale ||
                newDevicePixelRatio != m_devicePixelRatio)
            {
                m_dpiBasedScale = newDpiBasedScale;
                m_devicePixelRatio = newDevicePixelRatio;
                emit dpiChanged();
            }
        });

    m_widgetShown = true;
}

QWindow * DPIScalingHelper::nativeWindow() const
{
    auto window = m_widget->windowHandle();
    
    if (window)
        return window;
        
    auto nativeParent = m_widget->nativeParentWidget();
    
    if (!nativeParent)
        return nullptr;
        
    return nativeParent->windowHandle();
}

qreal DPIScalingHelper::fetchDpiBasedScale() const
{
#ifdef Q_OS_MAC
    return 1.0;
#else
    static const auto standardDpi = 96.0;

    auto window = nativeWindow();
    if (!window)
    {
        auto dpi = qApp->screens().first()->logicalDotsPerInch();
        return dpi / standardDpi;
    }
    
    auto dpi = window->screen()->logicalDotsPerInch();
    return dpi / standardDpi;
#endif
}

qreal DPIScalingHelper::fetchDevicePixelRatio() const
{
#ifdef Q_OS_MAC
    auto window = nativeWindow();
    if (!window)
        return qApp->screens().first()->devicePixelRatio();
    
    return window->devicePixelRatio();
#else
    return 1.0;
#endif
}

} // namespace propertyguizeug
