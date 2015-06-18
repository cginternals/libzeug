
#pragma once


#include <memory>
#include <functional>
#include <array>

#include <reflectionzeug/property/AbstractValueProperty.h>
#include <reflectionzeug/property/AbstractCollection.h>
#include <reflectionzeug/property/ArrayAccessor.h>


namespace reflectionzeug
{


template <typename Type>
class Property;


/**
*  @brief
*    Base class for typed array properties (read/write)
*/
template <typename Type, size_t Size>
class AbstractArrayProperty : public AbstractValueProperty<std::array<Type, Size>>
                            , public AbstractCollection
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    */
    AbstractArrayProperty(const std::string & name);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] defaultValue
    *    Default value that is set initially
    */
    AbstractArrayProperty(const std::string & name, const std::array<Type, Size> & value);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] getter
    *    Function to get an element of the array
    *  @param[in] setter
    *    Function to set an element of the array
    */
    AbstractArrayProperty(const std::string & name,
          std::function<Type (size_t)> getter,
          std::function<void(size_t, const Type &)> setter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get an element of the array
    *  @param[in] setter
    *    Method to set an element of the array
    */
    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, const Type &));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get an element of the array
    *  @param[in] setter
    *    Method to set an element of the array
    */
    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, const Type &));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get an element of the array
    *  @param[in] setter
    *    Method to set an element of the array
    */
    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, Type));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] accessor
    *    Accessor to get/set the value
    */
    AbstractArrayProperty(const std::string & name, ArrayAccessor<Type, Size> * accessor);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractArrayProperty();

    /**
    *  @brief
    *    Get array element
    *
    *  @param[in] i
    *    Index into array
    *
    *  @return
    *    Value
    */
    Type getElement(size_t i) const;

    /**
    *  @brief
    *    Set array element
    *
    *  @param[in] i
    *    Index into array
    *  @param[in] value
    *    Value
    */
    void setElement(size_t i, const Type & value);

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;

    // Virtual AbstractCollection interface
    virtual bool isEmpty() const override;
    virtual size_t count() const override;
    virtual AbstractProperty * at(size_t i) override;
    virtual const AbstractProperty * at(size_t i) const override;
    virtual int indexOf(const AbstractProperty * prop) const override;
    virtual void forEach(const std::function<void(AbstractProperty &)> & callback) override;
    virtual void forEach(const std::function<void(const AbstractProperty &)> & callback) const override;


protected:
    void init();


protected:
    ArrayAccessor<Type, Size>          * m_arrayAccessor; ///< Accessor to get/set the value
    std::array<Property<Type> *, Size>   m_elements;      ///< Elements as sub-properties
};


/**
*  @brief
*    Base class for typed array properties (read-only)
*/
template <typename Type, size_t Size>
class AbstractArrayProperty<const Type, Size> : public AbstractArrayProperty<Type, Size>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    */
    AbstractArrayProperty(const std::string & name);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] defaultValue
    *    Default value that is set initially
    */
    AbstractArrayProperty(const std::string & name, const std::array<Type, Size> & value);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] getter
    *    Function to get an element of the array
    */
    AbstractArrayProperty(const std::string & name, std::function<Type (size_t)> getter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get an element of the array
    */
    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)(size_t) const);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get an element of the array
    */
    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] accessor
    *    Accessor to get/set the value
    */
    AbstractArrayProperty(const std::string & name, ArrayAccessor<const Type, Size> * accessor);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractArrayProperty();
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractArrayProperty.hpp>
