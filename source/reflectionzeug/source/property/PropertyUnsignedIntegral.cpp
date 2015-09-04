
#include <reflectionzeug/property/PropertyUnsignedIntegral.h>


namespace reflectionzeug
{

template <>
bool setValueULL<bool>(PropertyUnsignedIntegral<bool> & p, const unsigned long long v)
{
	const auto b = v > 0;
	p.setValue(b);

	return true;
};

template <>
bool setValueULL<const bool>(PropertyUnsignedIntegral<const bool> & p, const unsigned long long v)
{
	const auto b = v > 0;
	p.setValue(b);

	return true;
};

/*
template <>
bool setValueULL<unsigned char>(PropertyUnsignedIntegral<unsigned char> & p, const unsigned long long v)
{
	p.setValue(static_cast<unsigned char>(v));
	return true;
};

template <>
bool setValueULL<unsigned int>(PropertyUnsignedIntegral<unsigned int> & p, const unsigned long long v)
{
	p.setValue(static_cast<unsigned int>(v));
	return true;
};


template <>
bool setValueULL<unsigned long>(PropertyUnsignedIntegral<unsigned long> & p, const unsigned long long v)
{
	p.setValue(static_cast<unsigned long>(v));
	return true;
};

template <>
bool setValueULL<unsigned __int64>(PropertyUnsignedIntegral<unsigned __int64> & p, const unsigned long long v)
{
	p.setValue(static_cast<unsigned __int64>(v));
	return true;
};*/

} // namespace reflectionzeug
