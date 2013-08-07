#include <Attribute.h>
#include <AttributeMap.h>

#include <algorithm>

Attribute::Attribute()
: _map(nullptr)
{
}

bool Attribute::isNumeric() const
{
	return false;
}

bool Attribute::isNominal() const
{
	return false;
}

void Attribute::setAttributeMap(const AttributeMap* map)
{
	_map = map;
}

double Attribute::normalizedValue() const
{
	if (!_map) return 0;

	return _map->normalize(this);
}

NumericAttribute* Attribute::asNumeric()
{
	return isNumeric() ? static_cast<NumericAttribute*>(this) : nullptr;
}

const NumericAttribute* Attribute::asNumeric() const
{
	return isNumeric() ? static_cast<const NumericAttribute*>(this) : nullptr;
}

NominalAttribute* Attribute::asNominal()
{
	return isNominal() ? static_cast<NominalAttribute*>(this) : nullptr;
}

const NominalAttribute* Attribute::asNominal() const
{
	return isNominal() ? static_cast<const NominalAttribute*>(this) : nullptr;
}

NumericAttribute::NumericAttribute()
: _value(0)
{
}

NumericAttribute::NumericAttribute(double value)
: _value(value)
{
}

bool NumericAttribute::isNumeric() const
{
	return true;
}

double NumericAttribute::value() const
{
	return _value;
}

double NumericAttribute::numericValue() const
{
	return _value;
}

void NominalType::addName(const std::string& name)
{
	_names.push_back(name);
}

int NominalType::valueFor(const std::string& name)
{
	std::vector<std::string>::iterator current = std::find(_names.begin(), _names.end(), name);
	
	if (current == _names.end())
	{
		return -1;
	}
	
	return std::distance(_names.begin(), current);
}

const std::string& NominalType::name(int value)
{
	return _names[value];
}

NominalAttribute* NominalType::newValue(const std::string& name)
{
	if (std::find(_names.begin(), _names.end(), name) == _names.end()) addName(name);

	return new NominalAttribute(*this, valueFor(name));
}

NominalAttribute::NominalAttribute(NominalType& type, int value)
: _type(type)
, _value(value)
{
}

bool NominalAttribute::isNominal() const
{
	return true;
}

int NominalAttribute::value() const
{
	return _value;
}

double NominalAttribute::numericValue() const
{
	return static_cast<double>(_value);
}

const std::string& NominalAttribute::valueName() const
{
	return _type.name(_value);
}

