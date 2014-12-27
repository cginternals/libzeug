#pragma once

#include <QWidget>

namespace widgetzeug
{

class ColorGradientModel;
class ColorGradientMidpointWidget;

class ColorGradientMidpointBar : public QWidget
{
    Q_OBJECT

public:
    ColorGradientMidpointBar(
        ColorGradientModel * model,
        QWidget * parent);
    
    ~ColorGradientMidpointBar();
    
signals:
    void resized(const QSize & size);
    
protected:
    void resizeEvent(QResizeEvent * event) override;

private:
    void initMidpoints();
    void clearMidpoints();

private:
    ColorGradientModel * m_model;
    QList<ColorGradientMidpointWidget *> m_stopWidgets;
};

} // namespace widgetzeug