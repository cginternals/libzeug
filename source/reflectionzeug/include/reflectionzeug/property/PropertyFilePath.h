
#pragma once


#include <reflectionzeug/base/FilePath.h>
#include <reflectionzeug/property/AbstractTypedProperty.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for type FilePath
*/
class REFLECTIONZEUG_API PropertyFilePath : public AbstractTypedProperty<FilePath>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyFilePath(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyFilePath();

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyFilePath.hpp>
