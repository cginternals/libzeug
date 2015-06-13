
#pragma once


#include <reflectionzeug/type/AbstractTyped.h>
#include <reflectionzeug/type/AbstractStringInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type std::string
*/
class TypedString : public AbstractTyped<std::string>, public AbstractStringInterface
{
public:
    template <typename... Args>
    TypedString(Args&&... args);

    virtual ~TypedString();

    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/TypedString.hpp>
