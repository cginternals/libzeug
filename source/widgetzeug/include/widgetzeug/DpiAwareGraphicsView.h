#pragma once

#include <QGraphicsView>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/DpiAware.h>


namespace widgetzeug
{

/** 
 * @brief QGraphicsView that implementsDpiAware trait
 */
class WIDGETZEUG_API DpiAwareGraphicsView : public QGraphicsView, protected DpiAware
{
    Q_OBJECT

public:
    DpiAwareGraphicsView(QWidget * parent = nullptr);
    DpiAwareGraphicsView(QGraphicsScene * scene, QWidget * parent = 0);

    virtual qreal dpiBasedScale() const;
    virtual qreal devicePixelRatio() const;

protected:
    virtual void showEvent(QShowEvent * event);

signals:
    void dpiChanged();
};

} // namespace widgetzeug
