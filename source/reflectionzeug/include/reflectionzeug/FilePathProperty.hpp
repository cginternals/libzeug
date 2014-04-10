
#pragma once

namespace reflectionzeug
{

template <typename... Arguments>
FilePathProperty::FilePathProperty(Arguments&&... args)
:   ClassProperty<FilePath>(std::forward<Arguments>(args)...)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

} // namespace reflectionzeug
