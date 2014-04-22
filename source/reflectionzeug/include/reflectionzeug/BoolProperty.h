
#pragma once

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/ValueProperty.h>


namespace reflectionzeug
{

class BoolProperty : public ValueProperty<bool>
{
public:
    template <typename... Arguments>
    BoolProperty(Arguments&&... args);

    REFLECTIONZEUG_API virtual std::string toString() const;
    REFLECTIONZEUG_API virtual bool fromString(const std::string & string);

    REFLECTIONZEUG_API void toggleValue();

};

} // namespace reflectionzeug

#include "BoolProperty.hpp"
