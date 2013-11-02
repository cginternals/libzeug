
#include <algorithm>

#include <treezeug/AttributeMap.h>
#include <treezeug/Attribute.h>


namespace zeug
{

Attribute::Attribute()
:   m_map(nullptr)
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
	m_map = map;
}

double Attribute::normalizedValue() const
{
	if (!m_map) return 0;

	return m_map->normalize(this);
}

double Attribute::normalizedValue2() const
{
	if (!m_map) return 0;

	return m_map->normalize2(this);
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
: m_value(0)
{
}

NumericAttribute::NumericAttribute(double value)
: m_value(value)
{
}

bool NumericAttribute::isNumeric() const
{
	return true;
}

double NumericAttribute::value() const
{
	return m_value;
}

double NumericAttribute::numericValue() const
{
	return m_value;
}

void NominalType::addName(const std::string & name)
{
	m_names.push_back(name);
}

int NominalType::valueFor(const std::string & name)
{
	std::vector<std::string>::iterator current = std::find(m_names.begin(), m_names.end(), name);
	
	if (current == m_names.end())
		return -1;
	
	return static_cast<int>(std::distance(m_names.begin(), current));
}

const std::string & NominalType::name(int value)
{
	return m_names[value];
}

NominalAttribute * NominalType::newValue(const std::string & name)
{
	if (std::find(m_names.begin(), m_names.end(), name) == m_names.end()) addName(name);

	return new NominalAttribute(*this, valueFor(name));
}




NominalAttribute::NominalAttribute(NominalType & type, int value)
:  m_type(type)
,  m_value(value)
{
}

bool NominalAttribute::isNominal() const
{
	return true;
}

int NominalAttribute::value() const
{
	return m_value;
}

double NominalAttribute::numericValue() const
{
	return static_cast<double>(m_value);
}

const std::string & NominalAttribute::valueName() const
{
	return m_type.name(m_value);
}

} // namespace zeug
