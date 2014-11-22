#pragma once

#include <QObject>

#include <propertyguizeug/propertyguizeug_api.h>

class QWidget;
class QWindow;

namespace propertyguizeug
{

class PROPERTYGUIZEUG_API DPIScalingHelper : public QObject
{
    Q_OBJECT

public:
    DPIScalingHelper(QWidget * parent);

    qreal dpiBasedScale() const;
    qreal devicePixelRatio() const;

    void widgetShown();

signals:
    void dpiChanged();

private:
    QWindow * nativeWindow() const;
    qreal fetchDpiBasedScale() const;
    qreal fetchDevicePixelRatio() const;

private:
    QWidget * m_widget;
    qreal m_dpiBasedScale;
    qreal m_devicePixelRatio;
    bool m_widgetShown;
};

} // namespace propertyguizeug
