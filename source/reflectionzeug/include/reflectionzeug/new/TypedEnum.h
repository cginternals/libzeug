
#pragma once


#include <string>
#include <vector>
#include <map>

#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for enum types
*/
template <typename Enum>
class TypedEnum : public AbstractTyped<Enum>
{
public:
    template <typename... Args>
    TypedEnum(Args&&... args);

    virtual ~TypedEnum();

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
    
    virtual std::vector<std::string> strings() const;
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
