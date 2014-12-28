#pragma once

#include <QPixmap>
#include <QWidget>

namespace widgetzeug
{

class ColorGradientModel;

class ColorGradientLabel : public QWidget
{
public:
    ColorGradientLabel(QWidget * parent);

    ColorGradientLabel(
        ColorGradientModel * model,
        QWidget * parent);
    
    void setModel(ColorGradientModel * model);

protected:
    void resizeEvent(QResizeEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    
private:
    void updatePixmap();

private:
    ColorGradientModel * m_model;
    QPixmap m_pixmap;
};

} // namespace widgetzeug