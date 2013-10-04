
#include <treeimportzeug/TreeXmlParser.h>
#include <treeimportzeug/TreeStrategy.h>

namespace zeug
{

TreeStrategy::TreeStrategy(TreeXmlParser & parser)
:   TreeXmlParserStrategy(parser)
{
}

bool TreeStrategy::startDocument()
{
	m_parser.tree()->addAttributeMap("size", AttributeMap::Numeric);

	return true;
}

bool TreeStrategy::endDocument()
{
	Node * root = m_parser.tree()->root();

	float totalSize = 0;
	root->childrenDo([&totalSize](Node * node) {
        totalSize += node->attribute("size")->numericValue(); });

	root->setName("<root>");
	root->setAttribute("size", totalSize);

	return true;
}

bool TreeStrategy::startElement(
    const QString & namespaceURI
,   const QString & localName
,   const QString & name
,   const QXmlAttributes & attributes)
{
	if (name != "directory" && name != "file")
		return true;

	if (m_stack.size() == 0)
	{
		m_stack.push(m_parser.tree()->root());
		return true;
	}

	Node * node = new Node();
	m_stack.top()->addChild(node);

	node->setName(attributes.value("name").toStdString());
	node->setAttribute("size", attributes.value("size").toFloat());

	m_stack.push(node);

	return true;
}

bool TreeStrategy::endElement(
    const QString & namespaceURI
,   const QString & localName
,   const QString & name)
{
	if (name != "directory" && name != "file")
		return true;

	m_stack.pop();
	return true;
}

bool TreeStrategy::characters(const QString & characters)
{
	return true;
}

} // namespace zeug
