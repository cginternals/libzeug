
#pragma once


#include <reflectionzeug/FilePath.h>
#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type FilePath
*/
class TypedFilePath : public TypedBase<FilePath>
{
public:
    TypedFilePath(Accessor<FilePath> * accessor);
    virtual ~TypedFilePath();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedFilePath.hpp>
