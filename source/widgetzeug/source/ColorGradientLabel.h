#pragma once

#include <QLabel>

namespace widgetzeug
{

class ColorGradientModel;

class ColorGradientLabel : public QLabel
{
public:
    ColorGradientLabel(QWidget * parent);

    ColorGradientLabel(
        ColorGradientModel * model,
        QWidget * parent);
    
    void setModel(ColorGradientModel * model);

protected:
    void resizeEvent(QResizeEvent * event) override;
    
public:
    void update();

private:
    ColorGradientModel * m_model;
};

} // namespace widgetzeug