#include <propertyzeug/DynObject.h>


/**
*  @brief
*    Constructor
*/
DynObject::DynObject()
{
}

/**
*  @brief
*    Destructor
*/
DynObject::~DynObject()
{
    // Delete attributes
    for (QHash<QString, AttributeBase*>::iterator it = m_mapAttributes.begin(); it != m_mapAttributes.end(); ++it)
        delete *it;

    // Clear attribute list
    m_mapAttributes.clear();
}

/**
*  @brief
*    Get child objects
*/
const QList<DynObject*> &DynObject::childObjects() const
{
    // Return child objects
    return m_childObjects;
}

/**
*  @brief
*    Add child object
*/
void DynObject::addChildObject(DynObject *obj)
{
    // Add child object to list
    m_childObjects.append(obj);
}

/**
*  @brief
*    Update child objects
*/
void DynObject::updateChildObjects()
{
    emit childrenUpdated();
}

/**
*  @brief
*    Remove all child objects
*/
void DynObject::clearChildObjects()
{
    // Remove child objects
    m_childObjects.clear();
}
