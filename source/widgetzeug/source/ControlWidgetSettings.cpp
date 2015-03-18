
#include <widgetzeug/ControlWidgetSettings.h>

#include <QSettings>
#include <QString>

#include <widgetzeug/ColorScheme.h>
#include <widgetzeug/ColorVisionDeficiency.h>
#include <widgetzeug/ColorSchemeControlWidget.h>


namespace
{
    
    static const QString KEY_COLORSCHEME_GEOMETRY   { "Geometry" };

    static const QString KEY_COLORSCHEME_FILENAME   { "FileName" };
    static const QString KEY_COLORSCHEME_FILENAMES  { "FileNames" };
    static const QString KEY_COLORSCHEME_FILELINKED { "FileLinked" };

    static const QString KEY_COLORSCHEME_SCHEME     { "Scheme" };
    static const QString KEY_COLORSCHEME_CLASSES    { "Classes" };
    static const QString KEY_COLORSCHEME_INVERTED   { "Inverted" };

    static const QString KEY_COLORSCHEME_TYPEFILTER{ "TypeFilter" };
    static const QString KEY_COLORSCHEME_CLASSESFILTER{ "ClassesFilter" };
    static const QString KEY_COLORSCHEME_DEFICIENCYFILTER{ "DeficiencyFilter" };
}

namespace widgetzeug
{
    
void ControlWidgetSettings::store(const QString & key, const ColorSchemeControlWidget & widget)
{
    QSettings settings;

    settings.beginGroup(key);

    settings.setValue(KEY_COLORSCHEME_GEOMETRY, widget.saveGeometry());

    settings.setValue(KEY_COLORSCHEME_FILENAME, widget.fileName());
    settings.setValue(KEY_COLORSCHEME_FILENAMES, widget.fileNames());
    settings.setValue(KEY_COLORSCHEME_FILELINKED, widget.fileLinked());

    if (widget.scheme())
        settings.setValue(KEY_COLORSCHEME_SCHEME, widget.scheme()->identifier());

    settings.setValue(KEY_COLORSCHEME_CLASSES, widget.classes());
    settings.setValue(KEY_COLORSCHEME_INVERTED, widget.inverted());

    settings.setValue(KEY_COLORSCHEME_TYPEFILTER, static_cast<int>(widget.typeFilter()));
    settings.setValue(KEY_COLORSCHEME_CLASSESFILTER, widget.classesFilter());
    settings.setValue(KEY_COLORSCHEME_DEFICIENCYFILTER, ColorScheme::s_deficiencies[widget.deficiency()]);

    settings.endGroup();
}

void ControlWidgetSettings::restore(const QString & key, ColorSchemeControlWidget & widget)
{
    QSettings settings;

    settings.beginGroup(key);

    if (settings.contains(KEY_COLORSCHEME_GEOMETRY))
        widget.restoreGeometry(settings.value(KEY_COLORSCHEME_GEOMETRY).toByteArray());

    if (settings.contains(KEY_COLORSCHEME_FILENAMES))
    {
        auto names = settings.value(KEY_COLORSCHEME_FILENAMES).toStringList();
        for (const auto & name : names)
            widget.addFileName(name);
    }
    if (settings.contains(KEY_COLORSCHEME_FILENAME))
        widget.setFileName(settings.value(KEY_COLORSCHEME_FILENAME).toString());
    if (settings.contains(KEY_COLORSCHEME_FILELINKED))
        widget.setFileLinked(settings.value(KEY_COLORSCHEME_FILELINKED).toBool());

    if (settings.contains(KEY_COLORSCHEME_SCHEME))
        widget.setScheme(settings.value(KEY_COLORSCHEME_SCHEME).toString());

    if (settings.contains(KEY_COLORSCHEME_CLASSES))
        widget.setClasses(settings.value(KEY_COLORSCHEME_CLASSES).toInt());
    if (settings.contains(KEY_COLORSCHEME_INVERTED))
        widget.setInverted(settings.value(KEY_COLORSCHEME_INVERTED).toBool());

    if (settings.contains(KEY_COLORSCHEME_TYPEFILTER))
        widget.setTypeFilter(static_cast<ColorScheme::ColorSchemeTypes>(settings.value(KEY_COLORSCHEME_TYPEFILTER).toInt()));
    if (settings.contains(KEY_COLORSCHEME_CLASSESFILTER))
        widget.setClassesFilter(settings.value(KEY_COLORSCHEME_CLASSESFILTER).toInt());
    if (settings.contains(KEY_COLORSCHEME_DEFICIENCYFILTER))
        widget.setDeficiency(ColorScheme::s_deficiencies.key(settings.value(KEY_COLORSCHEME_DEFICIENCYFILTER).toString()));

    settings.endGroup();
}

} // namespace widgetzeug
