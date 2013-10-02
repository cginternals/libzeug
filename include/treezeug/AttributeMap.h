#pragma once

#include <treezeug/Attribute.h>

#include <string>
#include <unordered_map>

class Node;

class AttributeMap
{
public:
	enum Type
	{
		None,
		Numeric,
		Nominal
	};

	AttributeMap(const std::string& name, Type type = Numeric);
	~AttributeMap();

	bool isNumeric() const;
	bool isNominal() const;

	const std::string& name() const;

	const Attribute* attributeFor(const Node* node) const;

	void addAttribute(const Node* node, double value);
	void addAttribute(const Node* node, const std::string& value);

	double normalize(const Attribute* value) const;
	
	Type type() const;
protected:
	std::string _name;
	Type _type;
	std::unordered_map<const Node*, Attribute*> _attributes;
	NominalType _nominalType;

	double _min;
	double _max;
	double _sum;

	void addAttribute(const Node* node, Attribute* value);

	Attribute* createNumeric(double value);
	Attribute* createNominal(const std::string& value);
};
