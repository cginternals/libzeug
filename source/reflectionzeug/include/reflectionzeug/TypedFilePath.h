
#pragma once


#include <reflectionzeug/base/FilePath.h>
#include <reflectionzeug/AbstractTyped.h>


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


#include <reflectionzeug/TypedFilePath.hpp>
