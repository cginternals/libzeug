
#include <reflectionzeug/new/Variant.h>
#include <reflectionzeug/new/Typed.h>


namespace reflectionzeug
{


Variant2::Variant2()
: m_value(nullptr)
{
}

Variant2::Variant2(const Variant2 & variant)
: m_value(nullptr)
{
    // [TODO]
}

Variant2::Variant2(int value)
: m_value(new Typed<int>(new AccessorValue<int>(value)))
{
}

Variant2::~Variant2()
{
    // [TODO]
    if (m_value)
    {
        delete m_value;
    }
}

int Variant2::toInt() const
{
    // Abort if value is empty
    if (!m_value)
    {
        return 0;
    }

    // Check if value has type int
    if (Typed<int> * typedInt = dynamic_cast<Typed<int>*>(m_value))
    {
        return typedInt->getValue();
    }

    // Check if value is a signed integral value
    else if (AbstractSignedIntegralInterface * signedIntegral = dynamic_cast<AbstractSignedIntegralInterface*>(m_value))
    {
        return (int)signedIntegral->toLongLong();
    }

    // Check if value is an unsigned integral value
    else if (AbstractUnsignedIntegralInterface * unsignedIntegral = dynamic_cast<AbstractUnsignedIntegralInterface*>(m_value))
    {
        return (int)unsignedIntegral->toULongLong();
    }

    // Check if value is a floating point value
    else if (AbstractFloatingPointInterface * floatingPoint = dynamic_cast<AbstractFloatingPointInterface*>(m_value))
    {
        return (int)floatingPoint->toDouble();
    }

    // Cannot convert value to int
    return 0;
}


} // namespace reflectionzeug
