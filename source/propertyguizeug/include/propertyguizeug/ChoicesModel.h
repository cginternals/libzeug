#pragma once

#include <QAbstractItemModel>
#include <QStringList>
#include <QList>
#include <QPixmap>

namespace reflectionzeug
{

class AbstractProperty;

}

namespace propertyguizeug
{

class ChoicesModel : public QAbstractItemModel
{
public:
    ChoicesModel(reflectionzeug::AbstractProperty * property);
    ChoicesModel(reflectionzeug::AbstractProperty * property, const std::vector<std::string> & choices);
    virtual ~ChoicesModel();

    bool hasIcons() const;
    QSize iconSize() const;

    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex & index) const override;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

protected:
    reflectionzeug::AbstractProperty * m_property;
    QStringList                        m_strings;
    QList<QPixmap>                     m_pixmaps;

protected:
    void obtainPixmaps();
};

} // namespace propertyguizeug
