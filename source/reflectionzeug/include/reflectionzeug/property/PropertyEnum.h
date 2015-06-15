
#pragma once


#include <string>
#include <vector>
#include <map>

#include <reflectionzeug/property/AbstractPropertyValue.h>
#include <reflectionzeug/property/AbstractEnumInterface.h>
#include <reflectionzeug/property/AbstractStringInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for enum types
*/
template <typename Enum>
class PropertyEnum : public AbstractPropertyValue<Enum>, public AbstractEnumInterface, public AbstractStringInterface
{
public:
    template <typename... Args>
    PropertyEnum(Args&&... args);

    virtual ~PropertyEnum();

    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    
    virtual std::vector<std::string> strings() const override;
    void setStrings(const std::map<Enum, std::string> & pairs);

    virtual void accept(AbstractVisitor * visitor) override;


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


#include <reflectionzeug/property/PropertyEnum.hpp>
