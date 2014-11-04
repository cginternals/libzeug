#pragma once

#include <reflectionzeug/ColorProperty.h>

namespace reflectionzeug
{

template <typename... Arguments>
ColorProperty::ColorProperty(Arguments&&... args)
:   ValueProperty<Color, ColorPropertyInterface>(std::forward<Arguments>(args)...)
{
}

} // namespace reflectionzeug
