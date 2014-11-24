#pragma once

#include <QGraphicsView>

#include <widgetzeug/widgetzeug_api.h>


namespace widgetzeug
{

class WIDGETZEUG_API DpiAwareGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    DpiAwareGraphicsView(QWidget * parent = nullptr);
    DpiAwareGraphicsView(QGraphicsScene * scene, QWidget * parent = nullptr);

    qreal dpiBasedScale() const;
    qreal invDevicePixelRatio() const;

protected:
    virtual void showEvent(QShowEvent * event);

signals:
    void dpiChanged();

private:
    QWindow * nativeWindow() const;
};

} // namespace widgetzeug
