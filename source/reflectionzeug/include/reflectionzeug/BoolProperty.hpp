
#pragma once

namespace reflectionzeug
{

template <typename... Arguments>
BoolProperty::BoolProperty(Arguments&&... args)
:   ValueProperty<bool>(std::forward<Arguments>(args)...)
{
}

} // namespace reflectionzeug
