#include <TreeStrategy.h>

#include <TreeXmlParser.h>

TreeStrategy::TreeStrategy(TreeXmlParser& parser)
: TreeXmlParserStrategy(parser)
{
}

bool TreeStrategy::startDocument()
{
	_parser.tree()->addAttributeMap("size", AttributeMap::Numeric);

	return true;
}

bool TreeStrategy::endDocument()
{
	Node* root = _parser.tree()->root();

	float totalSize = 0;
	root->childrenDo([&totalSize](Node* node) { totalSize += node->attribute("size")->numericValue(); });

	root->setName("<root>");
	root->setAttribute("size", totalSize);

	return true;
}

bool TreeStrategy::startElement(const QString& namespaceURI, const QString& localName, const QString& name, const QXmlAttributes& attributes)
{
	if (name != "directory" && name != "file")
	{
		return true;
	}

	if (_stack.size() == 0)
	{
		_stack.push(_parser.tree()->root());

		return true;
	}

	Node* node = new Node();
	_stack.top()->addChild(node);

	node->setName(attributes.value("name").toStdString());
	node->setAttribute("size", attributes.value("size").toFloat());

	_stack.push(node);

	return true;
}

bool TreeStrategy::endElement(const QString& namespaceURI, const QString& localName, const QString& name)
{
	if (name != "directory" && name != "file")
	{
		return true;
	}

	_stack.pop();

	return true;
}

bool TreeStrategy::characters(const QString& characters)
{
	return true;
}
