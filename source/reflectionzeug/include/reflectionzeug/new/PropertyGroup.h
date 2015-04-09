
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
    PropertyGroup2();
    virtual ~PropertyGroup2();
};


} // namespace reflectionzeug
