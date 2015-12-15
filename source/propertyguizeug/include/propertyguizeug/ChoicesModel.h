#pragma once

#include <QAbstractItemModel>
#include <QStringList>
#include <QList>
#include <QPixmap>

#include <propertyguizeug/propertyguizeug_api.h>


namespace reflectionzeug
{


class AbstractProperty;
class AbstractStringInterface;
class AbstractEnumInterface;


} // namespace reflectionzeug


namespace propertyguizeug
{

/**
 * @brief
 *    A helper class to enable icons for string and enum property editors.
 *
 *    It is a simple subclass of the QAbstractItemModel and overrides the methods required for a list model.
 *    The default behavior is to copy the required information for string lists with icons out of the property passed in the constructor.
 */
class PROPERTYGUIZEUG_API ChoicesModel : public QAbstractItemModel
{
public:
    /**
     * @brief This constructor is especially useful when handling string properties as it uses the strings, pixmaps and iconSize options.
     * @param property the string property
     */
    ChoicesModel(reflectionzeug::AbstractProperty * property);

    /**
     * @brief This constructor is especially useful when handling enum properties as it uses the choices passed as parameters in addition to the pixmaps and iconSize options.
     * @param property the enum property to create the editor on (required to extract the icon data)
     * @param choices the strings used for the dropdown and the matching with the pixmaps
     */
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
    reflectionzeug::AbstractProperty * m_property; /// the property this model operates on
    QStringList                        m_strings;  /// the list of strings for the dropdown list
    QList<QPixmap>                     m_pixmaps;  /// the according icons/pixmaps for the dropdown list

protected:
    void obtainPixmaps();
};


} // namespace propertyguizeug
