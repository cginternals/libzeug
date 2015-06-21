
#pragma once


#include <QString>

#include <reflectionzeug/property/Property.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for QString
*/
class PropertyQString : public reflectionzeug::AbstractValueProperty<QString>, public AbstractStringInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Arguments>
    PropertyQString(Arguments&&... args)
    : reflectionzeug::AbstractValueProperty<QString>(std::forward<Arguments>(args)...)
    {
    }

    // Virtual AbstractProperty interface
    virtual std::string toString() const override 
    {
        return this->value().toStdString();
    }

    virtual bool fromString(const std::string & string) override
    {
        this->setValue(QString::fromStdString(string));
        return true;
    }

    virtual Variant toVariant() const override
    {
        // Return string
        return Variant(this->value().toStdString());
    }

    virtual bool fromVariant(const Variant & value) override
    {
        // Read from string
        if (value.hasType<std::string>() || value.canConvert<std::string>()) {
            this->setValue(QString::fromStdString(value.value<std::string>()));
            return true;
        }

        // Invalid value
        return false;
    }

    virtual void accept(AbstractVisitor * visitor) override
    {
        visitor->callVisitor<PropertyQString>(this);
        visitor->callVisitor<AbstractStringInterface>(this);
    }
};

/**
*  @brief
*    Property selector for properties of type QString
*/
template <>
struct PropertyTypeSelector<QString>
{
    using Type = PropertyQString;
};


} // namespace reflectionzeug
