#pragma once

#include <string>
#include <unordered_map>

#include <treezeug/Attribute.h>


namespace zeug
{

class Node;

class AttributeMap
{
public:

    enum Type
	{
		None
    ,   Numeric
    ,   Nominal
	};

public:
	AttributeMap(
        const std::string & name
    ,   Type type = Numeric);

	~AttributeMap();

	bool isNumeric() const;
	bool isNominal() const;

	const std::string & name() const;

	const Attribute* attributeFor(const Node * node) const;

	void addAttribute(const Node * node, double value);
	void addAttribute(const Node * node, const std::string & value);

    /**
     * @brief Normalize between min_value and max_value.
     */
	double normalize(const Attribute * value) const;

    /**
     * @brief Normalize using the interval [ -max(abs(min_value), abs(max_value)), max(abs(min_value), abs(max_value)) ]
     */
    double normalize2(const Attribute * value) const;
	
	Type type() const;

protected:
    void addAttribute(const Node * node, Attribute * value);

	Attribute* createNumeric(double value);
	Attribute* createNominal(const std::string & value);

protected:
	std::string m_name;
	Type m_type;

	std::unordered_map<const Node*, Attribute*> m_attributes;
	NominalType m_nominalType;

	double m_min;
	double m_max;
	double m_sum;
};

} // namespace zeug
