
#pragma once


#include <reflectionzeug/FilePath.h>
#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type FilePath
*/
class TypedFilePath : public AbstractTyped<FilePath>
{
public:
    template <typename... Args>
    TypedFilePath(Args&&... args);

    virtual ~TypedFilePath();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedFilePath.hpp>
