
#pragma once


namespace reflectionzeug
{

/** \brief The template class of all instantiated properties.
 * Only this class may be instantiated!
 * Supported Types:
 * - bool
 * - int
 * - double
 * - std::string
 * - FilePath
 * - any std::array with type
 *   - bool
 *   - int
 *   - double
 * - any enum
 * - any class that implements (e.g. Color):
 *   - static Class fromString(std::string)
 *   - std::string toString()
 */
template <typename Type, typename = void>
class Property;

} // namespace reflectionzeug
