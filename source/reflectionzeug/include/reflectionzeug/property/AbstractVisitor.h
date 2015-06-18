
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


template <typename PropertyType, typename... MorePropertyTypes>
class Visitor;


/**
*  @brief
*    Base class for property visitors
*/
class REFLECTIONZEUG_API AbstractVisitor
{
public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    AbstractVisitor();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractVisitor();
    //@}

    //@{
    /**
    *  @brief
    *    Convert into visitor of type Visitor<Type>
    *
    *  @return
    *    Pointer to typed visitor, or nullptr if the visitor is not of the specified type
    */
    template <typename Type>
    Visitor<Type> * asVisitor();

    template <typename Type>
    Visitor<Type> * asVisitor() const;
    //@}

    //@{
    /**
    *  @brief
    *    Call visitor on typed property
    *
    *  @param[in] instance
    *    Property instance
    */
    template <typename Type>
    void callVisitor(Type * instance);
    //@}
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractVisitor.hpp>
