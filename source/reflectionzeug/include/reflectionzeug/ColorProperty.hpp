
#pragma once

namespace reflectionzeug
{

template <typename... Arguments>
ColorProperty::ColorProperty(Arguments&&... args)
:   ValueProperty<Color>(std::forward<Arguments>(args)...)
{
}

} // namespace reflectionzeug
