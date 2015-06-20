
#pragma once


#include <reflectionzeug/base/Color.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for color values
*
*    Used to access and edit color properties (regardless of the actual color class)
*    uniformly in the user interface.
*/
class REFLECTIONZEUG_API AbstractColorInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractColorInterface();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractColorInterface();

    /**
    *  @brief
    *    Convert value to color
    *
    *  @return
    *    Color value
    */
    virtual Color toColor() const = 0;

    /**
    *  @brief
    *    Convert value from color
    *
    *  @param[in] value
    *    Color value
    *
    *  @return
    *    'true' if the value could be set, else 'false'
    */
    virtual bool fromColor(const Color & color) = 0;
};


} // namespace reflectionzeug
