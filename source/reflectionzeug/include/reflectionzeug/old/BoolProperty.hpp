#pragma once

#include <reflectionzeug/BoolProperty.h>

namespace reflectionzeug
{

template <typename... Arguments>
BoolProperty::BoolProperty(Arguments&&... args)
:   ValueProperty<bool>(std::forward<Arguments>(args)...)
{
}

} // namespace reflectionzeug
