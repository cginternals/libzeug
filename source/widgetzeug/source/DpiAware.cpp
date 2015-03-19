
#include <widgetzeug/DpiAware.h>

#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QWidget>


namespace widgetzeug
{

QWindow * DpiAware::handle(const QWidget & widget)
{
    auto window = widget.windowHandle();

    if (window)
        return window;

    auto nativeParent = widget.nativeParentWidget();

    if (!nativeParent)
        return nullptr;

    return nativeParent->windowHandle();
}

qreal DpiAware::dpiBasedScale(const QWidget * widget)
{
#ifdef Q_OS_MAC
    return 1.f;
#else
    static const qreal standardDpi = 96.0;

    QWindow * window{ widget ? handle(*widget) : nullptr };

    if (!window)
    {
        auto dpi = qApp->screens().first()->logicalDotsPerInch();
        return dpi / standardDpi;
    }

    auto dpi = window->screen()->logicalDotsPerInch();
    return dpi / standardDpi;
#endif
}

qreal DpiAware::devicePixelRatio(const QWidget * widget)
{
    QWindow * window{ widget ? handle(*widget) : nullptr };

    if (!window)
        return qApp->screens().first()->devicePixelRatio();

    return window->devicePixelRatio();
}

} // namespace widgetzeug
