
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for properties
*/
class REFLECTIONZEUG_API AbstractProperty2
{
public:
    AbstractProperty2(const std::string & name);
    virtual ~AbstractProperty2();

    // [TODO]
    /*
    const VariantMap & options() const;
    Variant option(const std::string & key) const;

    template <typename T>
    T option(const std::string & key, const T & defaultValue) const;

    bool hasOption(const std::string & key) const;

    void setOption(const std::string & key, const Variant & value);
    void setOptions(const VariantMap & map);

    bool removeOption(const std::string & key);
    */


protected:
    std::string m_name; /**< Property name */
};


} // namespace reflectionzeug
