
#include <widgetzeug/ColorSchemeControlWidget.h>

#include <assert.h>

#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/ColorSchemePresets.h>
#include <widgetzeug/ColorSchemePresetsWidget.h>
#include <widgetzeug/ColorSchemeWidget.h>
#include <widgetzeug/DataLinkWidget.h>
#include <widgetzeug/make_unique.hpp>


namespace widgetzeug
{

ColorSchemeControlWidget::ColorSchemeControlWidget(
    const QString & title, QWidget * parent, const Qt::WindowFlags flags)
:   DockableScrollAreaWidget(title, parent, flags)
,   m_colorSchemeWidget{new ColorSchemeWidget{}}
,   m_colorSchemePresetsWidget{new ColorSchemePresetsWidget{}}
,   m_dataLinkWidget{new DataLinkWidget{}}
{
    m_dataLinkWidget->setReadOnly(true);
    m_dataLinkWidget->setWindowTitle(QObject::tr("Color Scheme Presets File"));
    m_dataLinkWidget->setFilter(QObject::tr("Color Scheme Presets Files") + " (*.json);;" + QObject::tr("All Files") + " (*.*)");

    const auto enabled = false;

    m_colorSchemeWidget->setEnabled(enabled);
    m_colorSchemePresetsWidget->setEnabled(enabled);

    addWidget(m_colorSchemeWidget);
    addWidget(m_colorSchemePresetsWidget);
    addWidget(m_dataLinkWidget);

    connect(m_colorSchemeWidget, &ColorSchemeWidget::classesChanged
        , this, &ColorSchemeControlWidget::classesChanged);

    connect(m_colorSchemeWidget, &ColorSchemeWidget::invertedChanged
        , this, &ColorSchemeControlWidget::invertedChanged);

    connect(m_colorSchemePresetsWidget, &ColorSchemePresetsWidget::selectedChanged
        , this, &ColorSchemeControlWidget::onSelectedChanged);

    connect(m_dataLinkWidget, &DataLinkWidget::fileChanged
        , this, &ColorSchemeControlWidget::onFileChanged);
}

ColorSchemeControlWidget::ColorSchemeControlWidget(
    QWidget * parent, const Qt::WindowFlags flags)
:   ColorSchemeControlWidget("", parent, flags)
{
}

void ColorSchemeControlWidget::addFileName(const QString & fileName, bool active)
{
    m_dataLinkWidget->addFileName(fileName, active);
}
void ColorSchemeControlWidget::setFileName(const QString & fileName)
{
    m_dataLinkWidget->setFileName(fileName);
}
const QString & ColorSchemeControlWidget::fileName() const
{
    return m_presets->fileName();
}

QStringList ColorSchemeControlWidget::fileNames() const
{
    return m_dataLinkWidget->fileNames();
}

void ColorSchemeControlWidget::setFileLinked(const bool linked)
{
    m_dataLinkWidget->setFileLinked(linked);
}
bool ColorSchemeControlWidget::fileLinked() const
{
    return m_dataLinkWidget->fileLinked();
}

const ColorSchemePresets * ColorSchemeControlWidget::presets() const
{
    return m_presets.get();
}

void ColorSchemeControlWidget::setScheme(const QString & identifier)
{
    m_colorSchemePresetsWidget->setSelected(identifier);
}

void ColorSchemeControlWidget::setScheme(const ColorScheme & scheme)
{
    m_colorSchemePresetsWidget->setSelected(scheme);
}
const ColorScheme * ColorSchemeControlWidget::scheme() const
{
    return m_colorSchemePresetsWidget->selected();
}

void ColorSchemeControlWidget::setTypeFilter(const ColorScheme::ColorSchemeTypes & types)
{
    m_colorSchemePresetsWidget->setTypeFilter(types);
}

ColorScheme::ColorSchemeTypes ColorSchemeControlWidget::typeFilter() const
{
    return m_colorSchemePresetsWidget->typeFilter();
}

void ColorSchemeControlWidget::setClasses(const uint classes)
{
    m_colorSchemeWidget->setClasses(classes);
}

uint ColorSchemeControlWidget::classes() const
{
    return m_colorSchemeWidget->classes();
}

void ColorSchemeControlWidget::setInverted(const bool invert)
{
    m_colorSchemeWidget->setInverted(invert);
}
bool ColorSchemeControlWidget::inverted() const
{
    return m_colorSchemeWidget->inverted();
}

void ColorSchemeControlWidget::setClassesFilter(const uint classes)
{
    m_colorSchemePresetsWidget->setClassesFilter(classes);
}

uint ColorSchemeControlWidget::classesFilter() const
{
    return m_colorSchemePresetsWidget->classesFilter();
}

void ColorSchemeControlWidget::setDeficiency(const ColorVisionDeficiency deficiency)
{
    m_colorSchemePresetsWidget->setDeficiency(deficiency);
}

ColorVisionDeficiency ColorSchemeControlWidget::deficiency() const
{
    return m_colorSchemePresetsWidget->deficiency();
}

void ColorSchemeControlWidget::onSelectedChanged(const ColorScheme * scheme)
{
    m_colorSchemeWidget->setScheme(scheme);
    emit schemeChanged(scheme);
}

void ColorSchemeControlWidget::onFileChanged(const QString & fileName)
{
    // this slot should be called by data link widget's file changes

    auto presets = make_unique<ColorSchemePresets>(fileName);
    m_dataLinkWidget->setFileIssue(!presets->isValid());

    if (!presets->isValid())
        return;

    m_lastPresetsFileName = fileName;
    const auto selected = m_colorSchemePresetsWidget->selected() ? 
        m_colorSchemePresetsWidget->selected()->identifier() : "";

    m_presets = std::move(presets);

    const auto enabled = static_cast<bool>(m_presets.get());
    assert(enabled);

    m_colorSchemeWidget->setScheme(nullptr);
    m_colorSchemeWidget->setEnabled(false);
    m_colorSchemePresetsWidget->setEnabled(enabled);

    //if (!enabled) // before: assert(enabled)
    //    return;

    m_colorSchemePresetsWidget->setPresets(*m_presets);

    const auto scheme = m_presets->scheme(selected);
    if (scheme)
        setScheme(*scheme);
    else
        setScheme(*m_presets->first()->first());

    m_colorSchemePresetsWidget->setEnabled(true);
}

} // namespace widgetzeug
