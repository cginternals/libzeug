
#pragma once


#include <reflectionzeug/FilePath.h>
#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type FilePath
*/
template <typename Accessor>
class TypedFilePath : public TypedBase<FilePath, Accessor>
{
public:
    TypedFilePath(const Accessor & accessor);
    virtual ~TypedFilePath();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedFilePath.hpp>
