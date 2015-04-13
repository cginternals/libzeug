
#include <widgetzeug/DpiAwareWidget.h>

#include <QWindow>
#include <QScreen>


namespace widgetzeug
{

DpiAwareWidget::DpiAwareWidget(QWidget * parent)
: QWidget{ parent }
{
}

qreal DpiAwareWidget::dpiBasedScale() const
{
    return DpiAware::dpiBasedScale(this);
}

qreal DpiAwareWidget::devicePixelRatio() const
{
    return DpiAware::devicePixelRatio(this);
}

void DpiAwareWidget::showEvent(QShowEvent * event)
{
    auto window = handle(*this);

    connect(window, &QWindow::screenChanged, this, &DpiAwareWidget::dpiChanged, Qt::UniqueConnection);

    emit dpiChanged();
}

} // namespace widgetzeug
