
#include <algorithm>
#include <limits>
#include <string>
#include <cassert>

#include <treezeug/AttributeMap.h>


namespace zeug
{

namespace 
{
	double to_double(const std::string & value)
	{
		if (value.empty())
		{
			return 0.0;
		}
		
		return std::stod(value);
	}
}


AttributeMap::AttributeMap(const std::string & name, Type type)
:   m_name(name)
,   m_type(type)
,   m_sum(0.0)
{
	m_max = -std::numeric_limits<double>::max();
	m_min = std::numeric_limits<double>::max();
}

AttributeMap::~AttributeMap()
{
	for (const std::pair<const Node* const, Attribute*> & pair : m_attributes)
	{
		delete pair.second;
	}
}

bool AttributeMap::isNumeric() const
{
	return m_type == Numeric;
}

bool AttributeMap::isNominal() const
{
	return m_type == Nominal;
}

const std::string & AttributeMap::name() const
{
	return m_name;
}

const Attribute* AttributeMap::attributeFor(const Node* node) const
{
	if (!m_attributes.count(node))
	{
		return nullptr;
	}
	
	return m_attributes.at(node);
}

void AttributeMap::addAttribute(const Node * node, double value)
{
	addAttribute(node,
		isNumeric() ? createNumeric(value) : createNominal(std::to_string(value))
	);
}

void AttributeMap::addAttribute(const Node * node, const std::string & value)
{
	addAttribute(node,
		isNumeric() ? createNumeric(to_double(value)) : createNominal(value)
	);
}

void AttributeMap::addAttribute(const Node * node, Attribute * value)
{
	assert(m_attributes.count(node) == 0);
	
	m_attributes[node] = value;
	value->setAttributeMap(this);
	
	m_min = std::min(m_min, value->numericValue());
	m_max = std::max(m_max, value->numericValue());

    m_sum += value->numericValue();
}

Attribute * AttributeMap::createNumeric(double value)
{
	return new NumericAttribute(value);
}

Attribute * AttributeMap::createNominal(const std::string & value)
{
	return m_nominalType.newValue(value);
}

double AttributeMap::normalize(const Attribute * value) const
{
	if (m_attributes.empty() || m_max - m_min == 0.0) return 0;
	
	return (value->numericValue() - m_min) / (m_max - m_min);
}

AttributeMap::Type AttributeMap::type() const
{
	return m_type;
}

} // namespace zeug
