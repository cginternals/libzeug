#pragma once

#include <type_traits>

#include <QtMath>


namespace widgetzeug
{

template <typename T>
const T & clamp(const T & value, const T & min, const T & max)
{
    return std::min(std::max(value, min), max);
}

template <typename T>
const T fract(const T & value)
{
    static_assert(std::is_floating_point<T>::value, "T must be a floating point type.");
    return value - qFloor(value);
}

template <typename T>
const T mix(const T & x, const T & y, qreal a)
{
    return (1.0 - a) * x + a * y;
}

} // namespace widgetzeug
