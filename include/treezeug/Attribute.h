#pragma once

#include <string>
#include <vector>

#include <treezeug/treezeug.h>

namespace zeug
{

class NumericAttribute;
class NominalAttribute;

class AttributeMap;

class TREEZEUG_API Attribute
{
public:
	Attribute();

	virtual bool isNumeric() const;
	virtual bool isNominal() const;

	NumericAttribute * asNumeric();
	const NumericAttribute* asNumeric() const;
	NominalAttribute * asNominal();
	const NominalAttribute * asNominal() const;

	virtual double numericValue() const = 0;

	double normalizedValue() const;
	double normalizedValue2() const;

	void setAttributeMap(const AttributeMap * map);

protected:
	const AttributeMap * m_map;
};


class TREEZEUG_API NumericAttribute : public Attribute
{
public:
	NumericAttribute();
	NumericAttribute(double value);

	virtual bool isNumeric() const;

	double value() const;
	virtual double numericValue() const;

protected:
	double m_value;
};


class TREEZEUG_API NominalType
{
public:
	int valueFor(const std::string & name);
	const std::string & name(int value);

	NominalAttribute * newValue(const std::string & name);

	void addName(const std::string & name);

protected:
	std::vector<std::string> m_names;
};


class TREEZEUG_API NominalAttribute : public Attribute
{
public:
	NominalAttribute(NominalType & type, int value);

	virtual bool isNominal() const;

	int value() const;
	const std::string & valueName() const;

	virtual double numericValue() const;

protected:
	NominalType & m_type;
	int m_value;
};

} // namespace zeug
