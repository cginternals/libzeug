
#pragma once

#include <array>


namespace reflectionzeug
{
 
/**
 * \brief The base class for value implementations of ArrayProperty.
 */
template <typename Type, size_t Size>
class AbstractArrayValue
{
public:
    virtual ~AbstractArrayValue() = default;
    
    virtual std::array<Type, Size> get() const = 0;
    virtual void set(const std::array<Type, Size> & array) = 0;

    virtual Type get(size_t i) const = 0;
    virtual void set(size_t i, const Type & value) = 0;

};

} // namespace reflectionzeug
