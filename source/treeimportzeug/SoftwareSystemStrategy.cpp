

#include <treeimportzeug/TreeXmlParser.h>
#include <treeimportzeug/SoftwareSystemStrategy.h>


namespace zeug
{

SoftwareSystemStrategy::SoftwareSystemStrategy(TreeXmlParser & parser)
:   TreeXmlParserStrategy(parser)
{
}

bool SoftwareSystemStrategy::startDocument()
{
	return true;
}

bool SoftwareSystemStrategy::endDocument()
{
	m_parser.tree()->root()->setName("<root>");

	return true;
}

bool SoftwareSystemStrategy::startElement(
    const QString & namespaceURI
,   const QString & localName
,   const QString & name
,   const QXmlAttributes & attributes)
{
	if (name != "directory" && name != "file")
	{
		if (name == "value")
		{
			QString fileId = attributes.value("fileId");
			QString value = attributes.value("value");

			if (m_nodes.count(fileId))
				m_nodes[fileId]->setAttribute(m_currentMetricName.toStdString(), value.toStdString());
		}
		else if (name == "metric")
		{
			QString name = attributes.value("name");
			QString valueType = attributes.value("valueType");

			m_currentMetricName = name;

			if (valueType == "String")
				m_parser.tree()->addAttributeMap(m_currentMetricName.toStdString(), AttributeMap::Nominal);
			else
				m_parser.tree()->addAttributeMap(m_currentMetricName.toStdString(), AttributeMap::Numeric);
		}

		return true;
	}

	if (m_stack.size() == 0)
	{
		m_stack.push(m_parser.tree()->root());
		return true;
	}

	Q_ASSERT(m_stack.top());

	Node * node = new Node();
	m_stack.top()->addChild(node);

	node->setName(attributes.value("name").toStdString());
	m_nodes[attributes.value("id")] = node;

	m_stack.push(node);

	return true;
}

bool SoftwareSystemStrategy::endElement(
    const QString & namespaceURI
,   const QString & localName
,   const QString & name)
{
	if (name != "directory" && name != "file")
		return true;

	m_stack.pop();
	return true;
}

bool SoftwareSystemStrategy::characters(const QString & characters)
{
	return true;
}

} // namespace zeug
