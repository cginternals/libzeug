
#pragma once


#include <reflectionzeug/base/FilePath.h>
#include <reflectionzeug/property/AbstractValueProperty.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type FilePath
*/
class PropertyFilePath : public AbstractValueProperty<FilePath>
{
public:
    template <typename... Args>
    PropertyFilePath(Args&&... args);

    virtual ~PropertyFilePath();

    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyFilePath.hpp>
