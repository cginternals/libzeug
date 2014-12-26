#pragma once

#include <QLabel>

namespace widgetzeug
{

class ColorGradientModel;

class ColorGradientLabel : public QLabel
{
public:
    ColorGradientLabel(
        ColorGradientModel * model,
        QWidget * parent = nullptr);

protected:
    void resizeEvent(QResizeEvent * event) override;
    
public:
    void update();

private:
    ColorGradientModel * m_model;
};

} // namespace widgetzeug