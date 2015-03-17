
#include <widgetzeug/ColorSchemePresets.h>

#include <memory>

#include <QMultiMap>
#include <QFile>
#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

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


ColorSchemePresets::ColorSchemePresets(const QString & fileName)
: QVector<ColorSchemeGroup *>()
, m_fileName{ fileName }
, m_valid{ false }
{
    reload();
}

ColorSchemePresets::~ColorSchemePresets()
{
    qDeleteAll(*this);
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
	m_valid = false;

    clear();

    QFile file{ m_fileName };

    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    const auto json = QString::fromUtf8(file.readAll());
    file.close();

	std::unique_ptr<QJsonParseError> jsonParseError{ new QJsonParseError };

	auto doc = QJsonDocument::fromJson(json.toUtf8(), jsonParseError.get());

	static const auto warning = QString("Cannot retrieve color scheme presets from Json \"%1\": ");
	if (jsonParseError->error != QJsonParseError::NoError)
	{
        qWarning() << qPrintable(warning.arg(m_fileName) + jsonParseError->errorString());
		return;
	}
	if (!doc.isObject())
	{
        qWarning() << qPrintable(warning.arg(m_fileName) + " document is not an object.");
		return;
	}
    auto presets = doc.object();

    m_valid = initialize(presets);
}

bool ColorSchemePresets::isValid() const
{
	return m_valid;
}

bool ColorSchemePresets::initialize(const QJsonObject & presets)
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
            return false;
        }

        if (!schemes.contains(CATEGORY_INDEX))
        {
            qWarning() << qPrintable(warning.arg(identifier) + "value object is missing category index.");
            return false;
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

	return !isEmpty();
}

} // namespace widgetzeug
