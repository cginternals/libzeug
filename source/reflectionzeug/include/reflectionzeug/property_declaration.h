
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
 * - Color
 * - FilePath
 * - std::vector<bool>
 * - std::vector<int>
 * - std::vector<double>
 * - any enum
 * - any class that implements:
 *   - static Class fromString(std::string)
 *   - std::string toString()
 */
template <typename Type, typename = void>
class Property;

} // namespace reflectionzeug
