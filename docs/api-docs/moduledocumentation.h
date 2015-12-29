
/**
 * \defgroup property_hierarchy Property Hierachy
 * \brief The heart of the property system.
 * 
 * Properties are devided into two groups:
 * - All classes of the first group inherit from AbstractValueProperty and represent a value.
 * - All classes of the second group inherit from AbstractPropertyCollection and represent a collection.
 *
 * The ArrayProperty is the only one that is in both groups. \n
 * Except PropertyGroup, you can't instantiate any of these classes directly.
 * Instead, you can use the Property template which dynamically inherits from the right class.
 *
 * \see \ref property_specializations
 */
