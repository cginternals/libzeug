
#pragma once


#include <functional>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


class AbstractProperty;
class AbstractVisitor;


/**
*  @brief
*    Interface for properties that are groups of other properties
*/
class REFLECTIONZEUG_API AbstractCollection
{
public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    AbstractCollection();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractCollection();

    /**
    *  @brief
    *    Accept visitor on all properties in the collection (recursively)
    *
    *  @param[in] visitor
    *    Visitor
    */
    void acceptRecursive(AbstractVisitor * visitor);

    /**
    *  @brief
    *    Check if collection is empty
    *
    *  @return
    *    'true' if the collection does not contain any properties, else 'false'
    */
    virtual bool isEmpty() const = 0;

    /**
    *  @brief
    *    Get number of properties in the collection
    *
    *  @return
    *    Number of properties
    */
    virtual size_t count() const = 0;
    //@}

    //@{
    /**
    *  @brief
    *    Get property in the collection
    *
    *  @param[in] i
    *    Index
    *
    *  @return
    *    Pointer to property, nullptr if index is invalid
    */
    virtual AbstractProperty * at(size_t i) = 0;
    virtual const AbstractProperty * at(size_t i) const = 0;
    //@}

    //@{
    /**
    *  @brief
    *    Get index of property in the collection
    *
    *  @param[in] prop
    *    Property
    *
    *  @return
    *    Index of the property in the collection, -1 if property does not belong to the collection
    */
    virtual int indexOf(const AbstractProperty * prop) const = 0;
    //@}

    //@{
    /**
    *  @brief
    *    Call function for each property in the collection
    *
    *  @param[in] callback
    *    Callback function
    */
    virtual void forEach(const std::function<void(AbstractProperty &)> & callback) = 0;
    virtual void forEach(const std::function<void(const AbstractProperty &)> & callback) const = 0;
    //@}
};


} // namespace reflectionzeug
