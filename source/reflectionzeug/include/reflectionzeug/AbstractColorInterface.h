
#pragma once


#include <reflectionzeug/Color.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for color values
*/
class REFLECTIONZEUG_API AbstractColorInterface
{
public:
    AbstractColorInterface();
    virtual ~AbstractColorInterface();

    virtual Color toColor() const = 0;
    virtual bool fromColor(const Color & color) = 0;
};


} // namespace reflectionzeug
