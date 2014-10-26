#pragma once

#include <reflectionzeug/FilePathProperty.h>

namespace reflectionzeug
{

template <typename... Arguments>
FilePathProperty::FilePathProperty(Arguments&&... args)
:   ClassProperty<FilePath>(std::forward<Arguments>(args)...)
{
}

} // namespace reflectionzeug
