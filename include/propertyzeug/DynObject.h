#pragma once


#include <QObject>
#include <QString>
#include <QHash>
#include <propertyzeug/Attribute.h>


/**
*  @brief
*    Object with dynamic attributes
*/
class DynObject : public QObject
{
    Q_OBJECT


    signals:
        void updateUI(const QString &attr);
        void childrenUpdated();


    public:
        /**
        *  @brief
        *    Constructor
        */
        PROPERTYZEUG_API DynObject();

        /**
        *  @brief
        *    Destructor
        */
        PROPERTYZEUG_API virtual ~DynObject();

        /**
        *  @brief
        *    Get child objects
        *
        *  @return
        *    List of child objects
        */
        PROPERTYZEUG_API const QList<DynObject*> &childObjects() const;

        /**
        *  @brief
        *    Add child object
        *
        *  @param[in] obj
        *    Child object
        */
        PROPERTYZEUG_API void addChildObject(DynObject *obj);

        /**
        *  @brief
        *    Update child objects
        *
        *  @remarks
        *    You must call this function after you have changed the child objects.
        *    It will emit the childrenUpdated() signal, so e.g. a GUI can update itself.
        */
        PROPERTYZEUG_API void updateChildObjects();

        /**
        *  @brief
        *    Remove all child objects
        *
        *  @remarks
        *    This removes all child objects from the object, but does not delete them!
        */
        PROPERTYZEUG_API void clearChildObjects();


    public:
        /**
        *  @brief
        *    Get attributes
        *
        *  @return
        *    List of attributes
        */
        const QList<AttributeBase*> &getAttributes() const
        {
            return m_attributes;
        }

        /**
        *  @brief
        *    Get attributes as hash map
        *
        *  @return
        *    Hash map of attributes
        */
        const QHash<QString, AttributeBase*> &getAttributeMap() const
        {
            return m_mapAttributes;
        }

        /**
        *  @brief
        *    Get attribute
        *
        *  @param[in] name
        *    Attribute name
        *
        *  @return
        *    Pointer to attribute, NULL on error
        */
        AttributeBase *getAttribute(const QString &name) const
        {
            return m_mapAttributes[name];
        }

        /**
        *  @brief
        *    Get attribute
        *
        *  @param[in] name
        *    Attribute name
        *
        *  @return
        *    Pointer to attribute, NULL on error
        */
        template <typename T>
        Attribute<T> *getAttribute(const QString &name) const
        {
            return (Attribute<T>*)m_mapAttributes[name];
        }

        /**
        *  @brief
        *    Add attribute
        *
        *  @param[in] attr
        *    Attribute
        */
        void addAttribute(AttributeBase *attr)
        {
            m_attributes   .append(attr);
            m_mapAttributes.insert(attr->getName(), attr);
        }

        /**
        *  @brief
        *    Add attribute
        *
        *  @param[in] name
        *    Attribute name
        *  @param[in] title
        *    Attribute title
        *  @param[in] obj
        *    Object holding the attribute
        *  @param[in] getFunc
        *    Name of getter function
        *  @param[in] setFunc
        *    Name of setter function
        */
        template <typename T>
        void addAttribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc)
        {
            Attribute<T> *attr = new Attribute<T>(name, title, obj, getFunc, setFunc);
            m_attributes   .append(attr);
            m_mapAttributes.insert(name, attr);
        }

        /**
        *  @brief
        *    Set attribute range
        *
        *  @param[in] name
        *    Attribute name
        *  @param[in] min
        *    Minimum value
        *  @param[in] max
        *    Maximum value
        */
        template <typename T>
        void setAttributeRange(const QString &name, T min, T max)
        {
            Attribute<T>* attr = (Attribute<T>*)m_mapAttributes[name];
            if (attr) {
                attr->setMinValue(min);
                attr->setMaxValue(max);
            }
        }

        /**
        *  @brief
        *    Set attribute tracking
        *
        *  @param[in] tracking
        *    'true' if attribute value shall be tracked, else 'false'
        *
        *  @remarks
        *    This parameter controls whether or not a parameter is updated on the fly, e.g. when using a slider to update the value
        */
        template <typename T>
        void setAttributeTracking(const QString &name, bool tracking)
        {
            Attribute<T>* attr = (Attribute<T>*)m_mapAttributes[name];
            if (attr) {
                attr->setTracking(tracking);
            }
        }

        /**
        *  @brief
        *    Get attribute value
        *
        *  @param[in] name
        *    Attribute name
        *
        *  @return
        *    Attribute value
        */
        template <typename T>
        T getAttr(const QString &name) const
        {
            Attribute<T>* attr = (Attribute<T>*)m_mapAttributes[name];
            if (attr) return attr->getValue();
            else      return Attribute<T>::NullValue();
        }

        /**
        *  @brief
        *    Set attribute value
        *
        *  @param[in] name
        *    Attribute name
        *  @param[in] value
        *    Attribute value
        */
        template <typename T>
        void setAttr(const QString &name, const T &value)
        {
            Attribute<T>* attr = (Attribute<T>*)m_mapAttributes[name];
            if (attr) attr->setValue(value);
        }


    protected:
        QHash<QString, AttributeBase*> m_mapAttributes; /**< List of dynamic attributes */
        QList<AttributeBase*>          m_attributes;    /**< List of dynamic attributes */
        QList<DynObject*>              m_childObjects;  /**< List of child objects */


};
