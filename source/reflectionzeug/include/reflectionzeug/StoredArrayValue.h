
#pragma once

#include <reflectionzeug/AbstractArrayValue.h>


namespace reflectionzeug
{
  
/**
 * \brief Provides access to a stored array value.
 */
template <typename Type, size_t Size>
class StoredArrayValue : public AbstractArrayValue<Type, Size>
{
public:
    StoredArrayValue(const std::array<Type, Size> & array);

    virtual std::array<Type, Size> get() const;
    virtual void set(const std::array<Type, Size> & array);

    virtual Type get(size_t i) const;
    virtual void set(size_t i, const Type & value);
    
private:
    std::array<Type, Size> m_array;
    
};

} // namespace reflectionzeug

#include "StoredArrayValue.hpp"
