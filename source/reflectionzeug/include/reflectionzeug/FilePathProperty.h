
#pragma once

#include <string>

#include <reflectionzeug/ClassProperty.h>
#include <reflectionzeug/FilePath.h>

#include <reflectionzeug/reflectionzeug_api.h>

namespace reflectionzeug
{
    
/**
 * \brief Extends the ClassProperty by some file path specific flags.
 */
class FilePathProperty : public ClassProperty<FilePath>
{
public:
    template <typename... Arguments>
    FilePathProperty(Arguments&&... args);

    REFLECTIONZEUG_API virtual ~FilePathProperty() = 0;

};

} // namespace reflectionzeug

#include "FilePathProperty.hpp"
