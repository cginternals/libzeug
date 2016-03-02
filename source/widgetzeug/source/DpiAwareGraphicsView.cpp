
#include <widgetzeug/DpiAwareGraphicsView.h>

#include <QWindow>
#include <QScreen>


namespace widgetzeug
{

DpiAwareGraphicsView::DpiAwareGraphicsView(QWidget * parent)
: QGraphicsView{ parent }
{
}

DpiAwareGraphicsView::DpiAwareGraphicsView(QGraphicsScene * scene, QWidget * parent)
: QGraphicsView{ scene, parent }
{
}

qreal DpiAwareGraphicsView::dpiBasedScale() const
{
    return DpiAware::dpiBasedScale(this);
}

qreal DpiAwareGraphicsView::devicePixelRatio() const
{
    return DpiAware::devicePixelRatio(this);
}

void DpiAwareGraphicsView::showEvent(QShowEvent * /*event*/)
{
    auto window = handle(*this);

    connect(window, &QWindow::screenChanged, this, &DpiAwareGraphicsView::dpiChanged, Qt::UniqueConnection);

    emit dpiChanged();
}

} // namespace widgetzeug
