#include <widgetzeug/DpiAwareGraphicsView.h>

#include <QApplication>
#include <QScreen>
#include <QWindow>


namespace widgetzeug
{

DpiAwareGraphicsView::DpiAwareGraphicsView(QWidget * parent)
:   QGraphicsView(parent)
{
}

DpiAwareGraphicsView::DpiAwareGraphicsView(QGraphicsScene * scene, QWidget * parent)
:   QGraphicsView(scene, parent)
{
}

qreal DpiAwareGraphicsView::dpiBasedScale() const
{
#ifdef Q_OS_MAC
    return 1.f;
#else
    static const qreal standardDpi = 96.f;

    QWindow * window = nativeWindow();
    if (!window)
    {
        qreal dpi = qApp->screens().first()->logicalDotsPerInch();
        return dpi / standardDpi;
    }
    
    qreal dpi = window->screen()->logicalDotsPerInch();
    return dpi / standardDpi;
#endif
}

qreal DpiAwareGraphicsView::invDevicePixelRatio() const
{
#ifdef Q_OS_MAC
    QWindow * window = nativeWindow();
    if (!window)
        return 1.f / qApp->screens().first()->devicePixelRatio();
    
    return 1.f / window->devicePixelRatio();
#else
    return 1.f;
#endif
}

void DpiAwareGraphicsView::showEvent(QShowEvent * event)
{
    QWindow * window = nativeWindow();
    
    connect(window, &QWindow::screenChanged,
            this, &DpiAwareGraphicsView::dpiChanged,
            Qt::UniqueConnection);
            
    emit dpiChanged();
}

QWindow * DpiAwareGraphicsView::nativeWindow() const
{
    QWindow * window = windowHandle();
    
    if (window)
        return window;
        
    QWidget * nativeParent = nativeParentWidget();
    
    if (!nativeParent)
        return nullptr;
        
    return nativeParent->windowHandle();
}

} // namespace widgetzeug
