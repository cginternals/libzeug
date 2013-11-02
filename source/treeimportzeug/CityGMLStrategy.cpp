
#include <treeimportzeug/TreeXmlParser.h>

#include <treeimportzeug/CityGMLStrategy.h>

namespace zeug
{

CityGMLStrategy::CityGMLStrategy(TreeXmlParser& parser)
: TreeXmlParserStrategy(parser)
, m_nextInformation(None)
{
}

bool CityGMLStrategy::startDocument()
{
	m_parser.tree()->addAttributeMap("size", AttributeMap::Numeric);

	return true;
}

bool CityGMLStrategy::endDocument()
{
	return true;
}

bool CityGMLStrategy::startElement(
    const QString & namespaceURI
,   const QString & localName
,   const QString & name
,   const QXmlAttributes & attributes)
{
	if (name == "node")
	{
		m_id = -1;
		m_label = QString();
		m_parentId = -1;
		m_size = -1;

		m_id = QString(attributes.value("id")).toInt();
	}
	else if (name == "label")
	{
		m_nextInformation = Label;
	}
	else if (name == "parentId")
	{
		m_nextInformation = ParentId;
	}
	else if (name == "size")
	{
		m_nextInformation = Size;
	}

	return true;
}

bool CityGMLStrategy::endElement(
    const QString & namespaceURI
,   const QString & localName
,   const QString & name)
{
	m_nextInformation = None;

	if (name != "node")
	{
		return true;
	}

	Node* node = new Node(m_id);

	if (m_id > 0)
	{
		Node* parent = m_parser.tree()->getNode(m_parentId);
		if (!parent)
		{
			parent = m_parser.tree()->root();
		}

		parent->addChild(node);
	}
	else if (m_id == 0)
		m_parser.tree()->setRoot(node);

	if (!m_label.isEmpty())
		node->setName(m_label.toStdString());

	if (m_size >= 0)
		node->setAttribute("size", m_size);

	return true;
}

bool CityGMLStrategy::characters(const QString & characters)
{
	switch (m_nextInformation)
	{
	case Label:
		m_label = characters;
		break;

	case ParentId:
		m_parentId = characters.toInt();
		break;

	case Size:
		m_size = characters.toInt();
		break;
	}

	return true;
}

} // namespace zeug
