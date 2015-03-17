#pragma once

#include <memory>

#include <widgetzeug/widgetzeug_api.h>

#include <widgetzeug/DockableScrollAreaWidget.h>
#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/ColorSchemePresets.h>


namespace widgetzeug
{

class ColorSchemePresets;
class ColorSchemePresetsWidget;
class ColorSchemeWidget;
class DataLinkWidget;


/** @brief Connects a color scheme presets widget with a data link widget.
 */
class WIDGETZEUG_API ColorSchemeControlWidget : public DockableScrollAreaWidget
{
    Q_OBJECT

public:
    ColorSchemeControlWidget(const QString & title, QWidget * parent = nullptr, Qt::WindowFlags flags = 0);
    ColorSchemeControlWidget(QWidget * parent = nullptr, Qt::WindowFlags flags = 0);

    virtual ~ColorSchemeControlWidget() = default;

	void setFileName(const QString & fileName);
	const QString & fileName() const;

	const ColorSchemePresets * presets() const;

    void setScheme(const ColorScheme & scheme);
    const ColorScheme * scheme();

    void setTypeFilter(const ColorScheme::ColorSchemeTypes & types);
    ColorScheme::ColorSchemeTypes typeFilter() const;

	void setClasses(uint classes);
	uint classes() const;

    void setClassesFilter(uint classes);
    uint classesFilter() const;

    void setDeficiency(ColorVisionDeficiency deficiency);
    ColorVisionDeficiency deficiency() const;

signals:
    void schemeChanged(const ColorScheme * scheme);
	void classesChanged(uint classes);

protected slots:
	void onSelectedChanged(const ColorScheme * scheme);
	void onClassesChanged(uint classes);
	void onFileChanged(const QString & fileName);

protected:
	ColorSchemeWidget * m_colorSchemeWidget;
    ColorSchemePresetsWidget * m_colorSchemePresetsWidget;
    DataLinkWidget * m_dataLinkWidget;

	std::unique_ptr<ColorSchemePresets> m_presets;
};

} // namespace widgetzeug
