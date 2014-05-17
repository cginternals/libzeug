
#pragma once

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/StringPropertyInterface.h>
#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{
    
/**
 * \brief Property implementation for strings.
 * \ingroup property_hierarchy
 */
class StringProperty : public StringPropertyInterface, public ValueProperty<std::string>
{
public:
    template <typename... Arguments>
    StringProperty(Arguments&&... args);
    
    REFLECTIONZEUG_API virtual ~StringProperty() = 0;

    REFLECTIONZEUG_API virtual void accept(AbstractPropertyVisitor * visitor);

    REFLECTIONZEUG_API virtual std::string toString() const;
    REFLECTIONZEUG_API virtual bool fromString(const std::string & string);
};

} // namespace reflectionzeug

#include "StringProperty.hpp"
