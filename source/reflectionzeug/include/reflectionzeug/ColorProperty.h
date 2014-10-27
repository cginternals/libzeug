#pragma once

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/ColorPropertyInterface.h>
#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{
    
/**
 * \brief Property implementation for strings.
 * \ingroup property_hierarchy
 */
class ColorProperty : public ColorPropertyInterface, public ValueProperty<Color>
{
public:
    using Type = Color;
    
public:
    template <typename... Arguments>
    ColorProperty(Arguments&&... args);
    
    REFLECTIONZEUG_API virtual ~ColorProperty() = 0;

    REFLECTIONZEUG_API virtual void accept(AbstractPropertyVisitor * visitor);

    REFLECTIONZEUG_API virtual Color toColor() const;
    REFLECTIONZEUG_API virtual bool fromColor(const Color & color);
};

} // namespace reflectionzeug

#include <reflectionzeug/ColorProperty.hpp>
