
#pragma once


#include <reflectionzeug/base/Color.h>

#include <reflectionzeug/variant/Variant.h>


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
    *    Convert color to HEX string
    *
    *  @param[in] includeAlpha
    *    Include the alpha value?
    *
    *  @return
    *    HEX color string ("#AARRGGBB"/"#RRGGBB")
    */
    std::string toHexString(bool includeAlpha = true) const;

    /**
    *  @brief
    *    Convert HEX string to color
    *
    *  @param[in] hex
    *    HEX color string ("#AARRGGBB")
    *
    *  @return
    *    'true' if string has been converted into color, 'false' on error
    */
    bool fromHexString(const std::string & hex);

    /**
    *  @brief
    *    Convert color to color variant
    *
    *  @return
    *    Variant ({ r: <r>, g: <g>, b: <b>, a: <a> })
    */
    Variant toColorVariant() const;

    /**
    *  @brief
    *    Convert color variant to color
    *
    *  @param[in] value
    *    Variant ({ r: <r>, g: <g>, b: <b>, a: <a> })
    *
    *  @return
    *    'true' if variant value has been converted into color, 'false' on error
    */
    bool fromColorVariant(const Variant & value);

    /**
    *  @brief
    *    Get color value as RGBA
    *
    *  @param[out] r
    *    Red value (0..255)
    *  @param[out] g
    *    Green value (0..255)
    *  @param[out] b
    *    Blue value (0..255)
    *  @param[out] a
    *    Alpha value (0..255)
    */
    virtual void getRGBA(int & r, int & g, int & b, int & a) const = 0;

    /**
    *  @brief
    *    Set color value as RGBA
    *
    *  @param[in] r
    *    Red value (0..255)
    *  @param[in] g
    *    Green value (0..255)
    *  @param[in] b
    *    Blue value (0..255)
    *  @param[in] a
    *    Alpha value (0..255)
    */
    virtual void setRGBA(int r, int g, int b, int a) = 0;

    /**
    *  @brief
    *    Get red color value
    *
    *  @return
    *    Red value (0..255)
    */
    virtual int red() const = 0;

    /**
    *  @brief
    *    Set red color value
    *
    *  @param[in] red
    *    Red value (0..255)
    */
    virtual void setRed(int red) = 0;

    /**
    *  @brief
    *    Get green color value
    *
    *  @return
    *    Green value (0..255)
    */
    virtual int green() const = 0;

    /**
    *  @brief
    *    Set green color value
    *
    *  @param[in] green
    *    Green value (0..255)
    */
    virtual void setGreen(int green) = 0;

    /**
    *  @brief
    *    Get blue color value
    *
    *  @return
    *    Blue value (0..255)
    */
    virtual int blue() const = 0;

    /**
    *  @brief
    *    Set blue color value
    *
    *  @param[in] blue
    *    Blue value (0..255)
    */
    virtual void setBlue(int blue) = 0;

    /**
    *  @brief
    *    Get alpha value
    *
    *  @return
    *    Alpha value (0..255)
    */
    virtual int alpha() const = 0;

    /**
    *  @brief
    *    Set alpha value
    *
    *  @param[in] alpha
    *    Alpha value (0..255)
    */
    virtual void setAlpha(int alpha) = 0;
};


} // namespace reflectionzeug
