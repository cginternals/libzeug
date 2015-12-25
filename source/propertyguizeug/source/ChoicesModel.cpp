#include <propertyguizeug/ChoicesModel.h>

#include <utility>

#include <reflectionzeug/property/AbstractProperty.h>

#include "util.h"

namespace propertyguizeug
{

ChoicesModel::ChoicesModel(reflectionzeug::AbstractProperty * property)
: m_property(property)
{
    if (m_property->hasOption("choices"))
    {
        auto choices = m_property->option("choices").value<std::vector<std::string>>();

        m_strings = util::toQStringList(choices);
    }

    obtainPixmaps();
}

ChoicesModel::ChoicesModel(reflectionzeug::AbstractProperty * property, const std::vector<std::string> & choices)
: m_property(property)
, m_strings(util::toQStringList(choices))
{
    obtainPixmaps();
}

ChoicesModel::~ChoicesModel()
{
}

void ChoicesModel::obtainPixmaps()
{
    if (hasIcons())
    {
        const auto pixmapSize = iconSize();
        const auto pixmaps = m_property->option("pixmaps").value<std::vector<std::vector<unsigned char>>>();

        for (const auto & pixmap : pixmaps)
        {
            const QImage image(pixmap.data(), pixmapSize.width(), pixmapSize.height(), QImage::Format_ARGB32);

            m_pixmaps.push_back(QPixmap::fromImage(image));
        }
    }
}

bool ChoicesModel::hasIcons() const
{
    return m_property->hasOption("pixmaps") && m_property->hasOption("pixmapSize");
}

QSize ChoicesModel::iconSize() const
{
    if (!hasIcons())
    {
        return { 0u, 0u };
    }

    const auto size = m_property->option("pixmapSize").value<std::pair<uint32_t, uint32_t>>();

    return QSize(size.first, size.second);
}

QModelIndex ChoicesModel::index(int row, int column, const QModelIndex & /* parent */) const
{
    return createIndex(row, column);
}

QModelIndex ChoicesModel::parent(const QModelIndex & /*index*/) const
{
    return QModelIndex();
}

int ChoicesModel::rowCount(const QModelIndex & /* parent */) const
{
    return qMax(m_strings.size(), m_pixmaps.size());
}

int ChoicesModel::columnCount(const QModelIndex & /* parent */) const
{
    return 1;
}

QVariant ChoicesModel::data(const QModelIndex & index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return m_strings.value(index.row(), "");
        break;
    case Qt::DecorationRole:
        return m_pixmaps.value(index.row(), QPixmap());
        break;
    default:
        return QVariant();
        break;
    }
}

} // namespace propertyguizeug
