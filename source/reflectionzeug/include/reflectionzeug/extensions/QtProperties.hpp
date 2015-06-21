
#pragma once


#include <QString>
#include <QColor>

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
*    Property implementation for QColor
*/
class PropertyQColor : public reflectionzeug::AbstractValueProperty<QColor>, public AbstractColorInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Arguments>
    PropertyQColor(Arguments&&... args)
    : reflectionzeug::AbstractValueProperty<QColor>(std::forward<Arguments>(args)...)
    {
    }

    // Virtual AbstractColorInterface interface
    virtual void getRGBA(int & r, int & g, int & b, int & a) const override
    {
        QColor color = this->value();
        r = color.red();
        g = color.green();
        b = color.blue();
        a = color.alpha();
    }

    virtual void setRGBA(int r, int g, int b, int a) override
    {
        this->setValue(QColor(r, g, b, a));
    }

    virtual int red() const override
    {
        return this->value().red();
    }

    virtual void setRed(int red) override
    {
        QColor color = this->value();
        color.setRed(red);
        this->setValue(color);
    }

    virtual int green() const override
    {
        return this->value().green();
    }

    virtual void setGreen(int green) override
    {
        QColor color = this->value();
        color.setGreen(green);
        this->setValue(color);
    }

    virtual int blue() const override
    {
        return this->value().blue();
    }

    virtual void setBlue(int blue) override
    {
        QColor color = this->value();
        color.setBlue(blue);
        this->setValue(color);
    }

    virtual int alpha() const override
    {
        return this->value().alpha();
    }

    virtual void setAlpha(int alpha) override
    {
        QColor color = this->value();
        color.setAlpha(alpha);
        this->setValue(color);
    }


    // Virtual AbstractProperty interface
    virtual std::string toString() const override 
    {
        // Return hex representation
        return toHexString();
    }

    virtual bool fromString(const std::string & string) override
    {
        // Read from hex representation
        return fromHexString(string);
    }

    virtual Variant toVariant() const override
    {
        // Return color as variant object
        return toColorVariant();
    }

    virtual bool fromVariant(const Variant & value) override
    {
        // Read from variant of the exact type
        if (value.hasType<QColor>() || value.canConvert<QColor>()) {
            setValue( value.value<QColor>() );
            return true;
        }

        // Read from string or object representation
        else {
            return fromColorVariant(value);
        }
    }

    virtual void accept(AbstractVisitor * visitor) override
    {
        visitor->callVisitor<PropertyQColor>(this);
        visitor->callVisitor<AbstractColorInterface>(this);
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

/**
*  @brief
*    Property selector for properties of type QColor
*/
template <>
struct PropertyTypeSelector<QColor>
{
    using Type = PropertyQColor;
};


} // namespace reflectionzeug
