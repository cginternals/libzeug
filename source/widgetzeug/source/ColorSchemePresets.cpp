
#include <widgetzeug/ColorSchemePresets.h>

#include <QFile>
#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>


#include <widgetzeug/ColorScheme.h>


namespace widgetzeug
{

ColorSchemeGroup::ColorSchemeGroup()
: m_identifier{ "" }
{
}

ColorSchemeGroup::ColorSchemeGroup(const QString & identifier, const QJsonObject & schemes)
: m_identifier{ identifier }
{
    if (schemes.isEmpty())
    {
        qWarning() << qPrintable("Cannot retrieve color schemes \"" + identifier + "\" from Json object: object is empty.");
        return;
    }

    for (const QString & identifier : schemes.keys())
        append(ColorScheme(identifier, schemes.value(identifier).toObject()));   
}

const QString & ColorSchemeGroup::identifier() const
{
    return m_identifier;
}


ColorSchemePresets::ColorSchemePresets()
{
}

ColorSchemePresets::ColorSchemePresets(const QString & fileName)
{
    QFile file{ fileName };

    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    const auto json = QString::fromUtf8(file.readAll());
    file.close();

    auto doc = QJsonDocument::fromJson(json.toUtf8());
    auto presets = doc.object();

    initialize(presets);
}

ColorSchemePresets::ColorSchemePresets(const QJsonObject & presets)
{
    initialize(presets);
}

void ColorSchemePresets::initialize(const QJsonObject & presets)
{
    static const auto warning = QString("Cannot retrieve color scheme category \"%1\" from Json object: ");

    auto categoryNamesByIndex = QMultiMap<int, QString>();

    static const auto CATEGORY_INDEX = QString{ "index" };


    for (const auto & identifier : presets.keys())
    {
        auto schemes = presets.value(identifier).toObject();
        if (schemes.isEmpty())
        {
            qWarning() << qPrintable(warning.arg(identifier) + "value object is empty.");
            return;
        }

        if (!schemes.contains(CATEGORY_INDEX))
        {
            qWarning() << qPrintable(warning.arg(identifier) + "value object is missing category index.");
            return;
        }

        const auto index = schemes.value(CATEGORY_INDEX).toInt();
        categoryNamesByIndex.insertMulti(index, identifier);
    }

    for (const auto index : categoryNamesByIndex.keys())
    {
        for (const auto & identifier : categoryNamesByIndex.values(index))
        {
            auto schemes = presets.value(identifier).toObject();
            schemes.take(CATEGORY_INDEX);

            append(ColorSchemeGroup(identifier, schemes));
        }
    }
}

} // namespace widgetzeug
