#pragma once

#include <string>
#include <vector>

class NumericAttribute;
class NominalAttribute;

class AttributeMap;

class Attribute
{
public:
	Attribute();

	virtual bool isNumeric() const;
	virtual bool isNominal() const;

	NumericAttribute* asNumeric();
	const NumericAttribute* asNumeric() const;
	NominalAttribute* asNominal();
	const NominalAttribute* asNominal() const;

	virtual double numericValue() const = 0;

	double normalizedValue() const;

	void setAttributeMap(const AttributeMap* map);
protected:
	const AttributeMap* _map;
};

class NumericAttribute : public Attribute
{
public:
	NumericAttribute();
	NumericAttribute(double value);

	virtual bool isNumeric() const;

	double value() const;
	virtual double numericValue() const;
protected:
	double _value;
};

class NominalType
{
public:
	int valueFor(const std::string& name);
	const std::string& name(int value);

	NominalAttribute* newValue(const std::string& name);
protected:
	std::vector<std::string> _names;

	void addName(const std::string& name);
};

class NominalAttribute : public Attribute
{
public:
	NominalAttribute(NominalType& type, int value);

	virtual bool isNominal() const;

	int value() const;
	const std::string& valueName() const;

	virtual double numericValue() const;
protected:
	NominalType& _type;
	int _value;
};
