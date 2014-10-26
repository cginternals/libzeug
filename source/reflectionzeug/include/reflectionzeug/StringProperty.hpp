#pragma once

#include <reflectionzeug/StringProperty.h>

namespace reflectionzeug
{

template <typename... Arguments>
StringProperty::StringProperty(Arguments&&... args)
:   ValueProperty<std::string>(std::forward<Arguments>(args)...)
{
}

} // namespace reflectionzeug
