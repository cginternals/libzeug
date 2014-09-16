
#pragma once

#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/FloatingPointPropertyInterface.h>


namespace reflectionzeug
{

/**
 * \brief Provides the property implementation for floating point types.
 *
 * While adding a precision member, it also implements the 
 * FloatingPointPropertyInterface
 *
 * \ingroup property_hierarchy
 */
template <typename Type>
class FloatingPointProperty : public FloatingPointPropertyInterface, public NumberProperty<Type>
{
public:
    template <typename... Arguments>
    FloatingPointProperty(Arguments&&... args);
    
    virtual ~FloatingPointProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual double toDouble() const;
    virtual bool fromDouble(double value);

protected:
    virtual std::string matchRegex() const;

};

} // namespace reflectionzeug

#include <reflectionzeug/FloatingPointProperty.hpp>
