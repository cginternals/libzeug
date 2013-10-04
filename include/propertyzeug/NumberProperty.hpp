
namespace zeug {

template <typename Type>
NumberProperty<Type>::NumberProperty(const std::string & name, const Type & value)
:   ValueProperty<Type>(name, value)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
NumberProperty<Type>::NumberProperty(const std::string & name, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   ValueProperty<Type>(name, getter, setter)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
template <class Object>
NumberProperty<Type>::NumberProperty(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   ValueProperty<Type>(name, object, getter_pointer, setter_pointer)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
template <class Object>
NumberProperty<Type>::NumberProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   ValueProperty<Type>(name, object, getter_pointer, setter_pointer)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
const Type & NumberProperty<Type>::minimum() const
{
    return m_min;
}

template <typename Type>
void NumberProperty<Type>::setMinimum(const Type & minimum)
{
    m_min = minimum;
    // this->m_announcer.notify(events::kRangeChanged);
}

template <typename Type>
const Type & NumberProperty<Type>::maximum() const
{
    return m_max;
}

template <typename Type>
void NumberProperty<Type>::setMaximum(const Type & maximum)
{
    m_max = maximum;
    // this->m_announcer.notify(events::kRangeChanged);
}
    
template <typename Type>
void NumberProperty<Type>::setRange(const Type & minimum, const Type & maximum)
{
    m_min = minimum;
    m_max = maximum;
    // this->m_announcer.notify(events::kRangeChanged);
}

template <typename Type>
bool NumberProperty<Type>::hasRanges() const
{
    return !(m_min == 0 && m_max == 0);
}
    
template <typename Type>
std::string NumberProperty<Type>::valueAsString() const
{
    std::stringstream stream;
    stream << this->value();
    return stream.str();
}

} // namespace
