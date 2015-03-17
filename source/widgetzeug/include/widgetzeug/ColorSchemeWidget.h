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

	void setDeficiency(ColorVisionDeficiency deficiency);

signals:
    void classesChanged(uint classes);

protected slots:
	void on_classesSpinBox_valueChanged(int value);

private:
	const ColorScheme * m_scheme;

	Ui_ColorSchemeWidget * m_ui;
};

} // namespace widgetzeug
