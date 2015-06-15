
#pragma once


#include <reflectionzeug/base/FilePath.h>
#include <reflectionzeug/type/AbstractPropertyValue.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type FilePath
*/
class TypedFilePath : public AbstractPropertyValue<FilePath>
{
public:
    template <typename... Args>
    TypedFilePath(Args&&... args);

    virtual ~TypedFilePath();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/TypedFilePath.hpp>
