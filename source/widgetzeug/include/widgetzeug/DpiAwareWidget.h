#pragma once

#include <QWidget>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/DpiAware.h>


namespace widgetzeug
{

/** 
 * @brief QWidget that implments the DpiAware trait
 */

class WIDGETZEUG_API DpiAwareWidget : public QWidget, protected DpiAware
{
    Q_OBJECT

public:
    DpiAwareWidget(QWidget * parent = nullptr);

    virtual qreal dpiBasedScale() const;
    virtual qreal devicePixelRatio() const;

protected:
    virtual void showEvent(QShowEvent * event);

signals:
    void dpiChanged();
};

} // namespace widgetzeug
