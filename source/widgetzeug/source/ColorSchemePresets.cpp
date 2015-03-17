
#include <widgetzeug/ColorSchemePresets.h>

#include <memory>

#include <QMultiMap>
#include <QFile>
#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>


#include <widgetzeug/ColorScheme.h>


namespace widgetzeug
{

ColorSchemeGroup::ColorSchemeGroup(const QString & identifier, const QJsonObject & schemes)
: QVector<ColorScheme *>()
, m_identifier{ identifier }
{
    if (schemes.isEmpty())
    {
        qWarning() << qPrintable("Cannot retrieve color schemes \"" + identifier + "\" from Json object: object is empty.");
        return;
    }

    for (const QString & i : schemes.keys())
        push_back(new ColorScheme(i, schemes.value(i).toObject()));
}

ColorSchemeGroup::~ColorSchemeGroup()
{
    qDeleteAll(*this);
}

const QString & ColorSchemeGroup::identifier() const
{
    return m_identifier;
}


// ToDo: remove when debugging is done
static auto num_instances = 0;


ColorSchemePresets::ColorSchemePresets(const QString & fileName)
: QVector<ColorSchemeGroup *>()
, m_fileName{ fileName }
{
	++num_instances;
	qDebug() << "\t*ColorSchemePresets " << static_cast<void*>(this) << " " << num_instances;

    reload();
}

ColorSchemePresets::~ColorSchemePresets()
{
    qDeleteAll(*this);
	--num_instances;
	qDebug() << "\t~ColorSchemePresets " << static_cast<void*>(this) << " " << num_instances;
}

void ColorSchemePresets::setFileName(const QString & fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    reload();
}

const QString & ColorSchemePresets::fileName() const
{
    return m_fileName;
}

void ColorSchemePresets::reload()
{
    clear();

    QFile file{ m_fileName };

    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    const auto json = QString::fromUtf8(file.readAll());
    file.close();

    auto doc = QJsonDocument::fromJson(json.toUtf8());
    auto presets = doc.object();

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

            push_back(new ColorSchemeGroup(identifier, schemes));
        }
    }
}

} // namespace widgetzeug
