
#include <widgetzeug/ColorScheme.h>

#include <assert.h>

#include <QDebug>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>


namespace widgetzeug
{

const QMap<ColorScheme::ColorSchemeType, QString> ColorScheme::s_types = {
    { ColorSchemeType::Unknown,     "Unknown" },
    { ColorSchemeType::Sequential,  "Sequential" },
    { ColorSchemeType::Diverging,   "Diverging" },
    { ColorSchemeType::Qualitative, "Qualitative" } };

const QMap<ColorVisionDeficiency, QString> ColorScheme::s_deficiencies = {
    { ColorVisionDeficiency::None, "None" },
    { ColorVisionDeficiency::Protanope, "Protanope" },
    { ColorVisionDeficiency::Deuteranope, "Deuteranope" },
    { ColorVisionDeficiency::Tritanope, "Tritanope" },
    { ColorVisionDeficiency::Grayscale, "Grayscale" } };


// ToDo: remove when debugging is done
static auto num_instances = 0;


ColorScheme::ColorScheme()
: ColorScheme{ "", Unknown }
{
}

ColorScheme::ColorScheme(const QString & identifier)
: ColorScheme{ identifier, Unknown }
{
}

ColorScheme::ColorScheme(const QString & identifier, ColorSchemeType type)
: m_identifier{ identifier }
, m_type{ type }
{
	++num_instances;
	qDebug() << "\t*ColorScheme " << static_cast<void*>(this) << " " << num_instances;
}

ColorScheme::ColorScheme(const QString & identifier, QJsonObject scheme)
: m_identifier{ identifier }
{
	++num_instances;
	qDebug() << "\t*ColorScheme " << static_cast<void*>(this) << " " << num_instances;

    if (scheme.isEmpty())
    {
        qWarning() << qPrintable("Cannot retrieve color scheme \"" + identifier + "\" from Json object: object is empty.");
        return;
    }

    static const auto TYPE_KEY = QString{ "type" };
    if (scheme.contains(TYPE_KEY))
    {
        auto type = scheme.take(TYPE_KEY).toString();
        if (s_types.values().contains(type))
            setType(s_types.key(type));
    }

    for (const auto & c : scheme.keys())
    {
        int classes = c.toInt();

        assert(scheme.value(c).isArray());
        auto array = scheme.value(c).toArray();

        if (array.isEmpty())
            continue;

        QVector<QColor> colors;

        for (int i = 0; i < classes; ++i)
        {
            auto color = array[i].toString();
            color = color.mid(1, color.length() - 2);
            color.replace(" ", "");

            auto rgb = color.split(",");

            bool ok[3];
            const int r = rgb[0].toInt(&ok[0]);
            const int g = rgb[1].toInt(&ok[1]);
            const int b = rgb[2].toInt(&ok[2]);

            if (!ok[0] || !ok[1] || !ok[2])
            {
                qWarning() << qPrintable("Parsing of \"" + array[i].toString() + "\" in color scheme \"" + identifier + "\" failed: using default color.");
                colors << Qt::white;
            }
            else
                colors << QColor(r, g, b);
        }
        setColors(colors);
    }
}

ColorScheme::~ColorScheme()
{
	--num_instances;
	qDebug() << "\t~ColorScheme " << static_cast<void*>(this) << " " << num_instances;
}

bool ColorScheme::operator==(const ColorScheme & scheme) const
{
    return m_colorsByClass == scheme.m_colorsByClass;
}

void ColorScheme::setColors(const QVector<QColor> & colors)
{
    m_colorsByClass[colors.size()] = colors;
}

const QVector<QColor> ColorScheme::colors(uint classes) const
{
    if (!m_colorsByClass.contains(classes))
        return QVector<QColor>();

    return m_colorsByClass[classes];    
}

void ColorScheme::setIdentifier(const QString & identifier)
{
    m_identifier = identifier;
}

const QString & ColorScheme::identifier() const
{
    return m_identifier;
}

void ColorScheme::setType(ColorSchemeType type)
{
    m_type = type;
}

ColorScheme::ColorSchemeType ColorScheme::type() const
{
    return m_type;
}

uint ColorScheme::minClasses() const
{
    return m_colorsByClass.firstKey();
}

uint ColorScheme::maxClasses() const
{
    return m_colorsByClass.lastKey();
}

Q_DECLARE_OPERATORS_FOR_FLAGS(ColorScheme::ColorSchemeTypes)

} // namespace widgetzeug

//bool operator ==(const widgetzeug::ColorScheme & a, const widgetzeug::ColorScheme & b)
//{
//    return a.identifier() == b.identifier();
//}
