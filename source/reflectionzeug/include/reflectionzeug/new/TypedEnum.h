
#pragma once


#include <string>
#include <vector>
#include <map>

#include <reflectionzeug/new/AbstractTyped.h>
#include <reflectionzeug/new/AbstractEnumInterface.h>
#include <reflectionzeug/new/AbstractStringInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for enum types
*/
template <typename Enum>
class TypedEnum : public AbstractTyped<Enum>, public AbstractEnumInterface, public AbstractStringInterface
{
public:
    template <typename... Args>
    TypedEnum(Args&&... args);

    virtual ~TypedEnum();

    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    
    virtual std::vector<std::string> strings() const override;
    void setStrings(const std::map<Enum, std::string> & pairs);


protected:
    std::map<Enum, std::string> m_stringMap;
    std::map<std::string, Enum> m_enumMap;
};


/**
 * @brief
 *    Specialize this template to provide default string mapping for an enum.
 */
template <typename Enum>
struct EnumDefaultStrings
{
    std::map<Enum, std::string> operator()()
    {
        return std::map<Enum, std::string>();
    }
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedEnum.hpp>
