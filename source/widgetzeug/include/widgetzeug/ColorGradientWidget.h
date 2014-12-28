#pragma once

#include <memory>

#include <QDialog>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorGradient.h>

class QDialogButtonBox;
class QLabel;

class Ui_ColorGradientWidget;

namespace widgetzeug
{

class ColorGradientLabel;
class ColorGradientMidpointBar;
class ColorGradientModel;
class ColorGradientStopBar;

class WIDGETZEUG_API ColorGradientWidget : public QDialog
{
    Q_OBJECT

public:
    ColorGradientWidget(
        const ColorGradient & gradient,
        QWidget * parent = nullptr);
    
    ~ColorGradientWidget();
    
    ColorGradient gradient() const;
    
private:
    std::unique_ptr<ColorGradientModel> m_model;
    Ui_ColorGradientWidget * m_ui;
};

} // namespace widgetzeug
