#include <CityGMLStrategy.h>

#include <TreeXmlParser.h>

CityGMLStrategy::CityGMLStrategy(TreeXmlParser& parser)
: TreeXmlParserStrategy(parser)
, _nextInformation(None)
{
}

bool CityGMLStrategy::startDocument()
{
	_parser.tree()->addAttributeMap("size", AttributeMap::Numeric);

	return true;
}

bool CityGMLStrategy::endDocument()
{
	return true;
}

bool CityGMLStrategy::startElement(const QString& namespaceURI, const QString& localName, const QString& name, const QXmlAttributes& attributes)
{
	if (name == "node")
	{
		_id = -1;
		_label = QString();
		_parentId = -1;
		_size = -1;

		_id = QString(attributes.value("id")).toInt();
	}
	else if (name == "label")
	{
		_nextInformation = Label;
	}
	else if (name == "parentId")
	{
		_nextInformation = ParentId;
	}
	else if (name == "size")
	{
		_nextInformation = Size;
	}

	return true;
}

bool CityGMLStrategy::endElement(const QString& namespaceURI, const QString& localName, const QString& name)
{
	_nextInformation = None;

	if (name != "node")
	{
		return true;
	}

	Node* node = new Node(_id);

	if (_id > 0)
	{
		Node* parent = _parser.tree()->getNode(_parentId);
		if (!parent)
		{
			parent = _parser.tree()->root();
		}

		parent->addChild(node);
	}
	else if (_id == 0)
	{
		_parser.tree()->setRoot(node);
	}

	if (!_label.isEmpty())
	{
		node->setName(_label.toStdString());
	}

	if (_size >= 0)
	{
		node->setAttribute("size", _size);
	}

	return true;
}

bool CityGMLStrategy::characters(const QString& characters)
{
	switch (_nextInformation)
	{
		case Label:
			_label = characters;
			break;
		case ParentId:
			_parentId = characters.toInt();
			break;
		case Size:
			_size = characters.toInt();
			break;
	}

	return true;
}
