#pragma once

#include <QWidget>

#include <widgetzeug/widgetzeug_api.h>
#include <widgetzeug/ColorVisionDeficiency.h>


class Ui_ColorSchemeWidget;

namespace widgetzeug
{
class ColorScheme;


class WIDGETZEUG_API ColorSchemeWidget : public QWidget
{
    Q_OBJECT

public:
    ColorSchemeWidget(QWidget * parent = nullptr);
    virtual ~ColorSchemeWidget();

    void setScheme(const ColorScheme * scheme);

    void setClasses(uint classes);
    uint classes() const;

    void setInverted(bool invert);
    bool inverted() const;

    void setDeficiency(ColorVisionDeficiency deficiency);

signals:
    void classesChanged(uint classes);
    void invertedChanged(bool inverted);

protected slots:
    void on_classesSpinBox_valueChanged(int value);
    void on_invertedCheckBox_toggled(bool checked);

private:
    Ui_ColorSchemeWidget * m_ui;

    const ColorScheme * m_scheme;
};

} // namespace widgetzeug
