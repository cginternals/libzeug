
#pragma once


#include <reflectionzeug/new/AbstractProperty.h>
#include <reflectionzeug/new/AbstractCollection.h>
#include <reflectionzeug/new/AbstractValue.h>


namespace reflectionzeug
{


/**
*  @brief
*    Group of properties
*/
class REFLECTIONZEUG_API PropertyGroup2 : public AbstractProperty2,
                                          public AbstractCollection,
                                          public AbstractValue
{
public:
    PropertyGroup2(const std::string & name);
    virtual ~PropertyGroup2();

    virtual std::string name() const override;
    virtual bool setName(const std::string & name) override;
};


} // namespace reflectionzeug
