
#pragma once


#include <string>

#include <reflectionzeug/new/Typed.h>


namespace reflectionzeug
{


/**
*  @brief
*    Typed value with a name
*/
template <typename T>
class NamedTyped : public Typed<T>
{
public:
    template <typename... Args>
    NamedTyped(const std::string & name, Args&&... args);

    virtual ~NamedTyped();

    virtual std::string name() const override;
    virtual bool setName(const std::string & name) override;


protected:
    std::string m_name;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/NamedTyped.hpp>
