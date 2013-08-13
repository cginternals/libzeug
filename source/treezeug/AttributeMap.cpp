#include <AttributeMap.h>

#include <limits>
#include <string>
#include <cassert>

namespace {
	double to_double(const std::string& value)
	{
		if (value.empty())
		{
			return 0.0;
		}
		
		return std::stod(value);
	}
}

AttributeMap::AttributeMap(const std::string& name, Type type)
: _name(name)
, _type(type)
, _sum(0.0)
{
	_max = -std::numeric_limits<double>::max();
	_min = std::numeric_limits<double>::max();
}

AttributeMap::~AttributeMap()
{
	for (const std::pair<const Node* const, Attribute*>& pair : _attributes)
	{
		delete pair.second;
	}
}

bool AttributeMap::isNumeric() const
{
	return _type == Numeric;
}

bool AttributeMap::isNominal() const
{
	return _type == Nominal;
}

const std::string& AttributeMap::name() const
{
	return _name;
}

const Attribute* AttributeMap::attributeFor(const Node* node) const
{
	if (!_attributes.count(node))
	{
		return nullptr;
	}
	
	return _attributes.at(node);
}

void AttributeMap::addAttribute(const Node* node, double value)
{
	addAttribute(node,
		isNumeric() ? createNumeric(value) : createNominal(std::to_string(value))
	);
}

void AttributeMap::addAttribute(const Node* node, const std::string& value)
{
	addAttribute(node,
		isNumeric() ? createNumeric(to_double(value)) : createNominal(value)
	);
}

void AttributeMap::addAttribute(const Node* node, Attribute* value)
{
	assert(_attributes.count(node) == 0);
	
	_attributes[node] = value;
	value->setAttributeMap(this);
	
	_min = std::min(_min, value->numericValue());
	_max = std::max(_max, value->numericValue());
	_sum += value->numericValue();
}

Attribute* AttributeMap::createNumeric(double value)
{
	return new NumericAttribute(value);
}

Attribute* AttributeMap::createNominal(const std::string& value)
{
	return _nominalType.newValue(value);
}

double AttributeMap::normalize(const Attribute* value) const
{
	if (_attributes.empty() || _max - _min == 0.0) return 0;
	
	return (value->numericValue() - _min) / (_max - _min);
}
