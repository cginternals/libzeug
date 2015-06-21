
#pragma once


#include <string>
#include <vector>
#include <map>

#include <reflectionzeug/property/AbstractTypedProperty.h>
#include <reflectionzeug/property/AbstractEnumInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for enum types
*/
template <typename Enum>
class PropertyEnum : public AbstractTypedProperty<Enum>, public AbstractEnumInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyEnum(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyEnum();

    /**
    *  @brief
    *    Get available choices
    *
    *  @return
    *    List of values
    */
    const std::vector<Enum> & choices() const;

    /**
    *  @brief
    *    Set available choices
    *
    *  @param[in] choices
    *    List of values
    */
    void setChoices(const std::vector<Enum> & choices);

    /**
    *  @brief
    *    Set available enum values
    *
    *  @param[in] pairs
    *    List of values and names
    */
    void setStrings(const std::map<Enum, std::string> & pairs);

    // Virtual AbstractEnumInterface interface
    virtual std::vector<std::string> strings() const override;
    virtual bool hasChoices() const override;
    virtual std::vector<std::string> choicesStrings() const override;

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;
    virtual void accept(AbstractVisitor * visitor) override;


protected:
    std::map<Enum, std::string> m_stringMap;
    std::map<std::string, Enum> m_enumMap;
    std::vector<Enum> m_choices;
};


/**
*  @brief
*    Default value mapping for enum type
*
*    Specialize this template to provide a default string mapping for an enum.
*/
template <typename Enum>
struct EnumDefaultStrings
{
    /**
    *  @brief
    *    Return available enum values and their string representations
    *
    *  @return
    *    Map of values and strings
    */
    std::map<Enum, std::string> operator()();
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyEnum.hpp>
