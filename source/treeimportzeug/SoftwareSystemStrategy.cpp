#include <SoftwareSystemStrategy.h>

#include <TreeXmlParser.h>

SoftwareSystemStrategy::SoftwareSystemStrategy(TreeXmlParser& parser)
: TreeXmlParserStrategy(parser)
{
}

bool SoftwareSystemStrategy::startDocument()
{
	return true;
}

bool SoftwareSystemStrategy::endDocument()
{
	_parser.tree()->root()->setName("<root>");

	return true;
}

bool SoftwareSystemStrategy::startElement(const QString& namespaceURI, const QString& localName, const QString& name, const QXmlAttributes& attributes)
{
	if (name != "directory" && name != "file")
	{
		if (name == "value")
		{
			QString fileId = attributes.value("fileId");
			QString value = attributes.value("value");

			if (_nodes.count(fileId))
			{
				_nodes[fileId]->setAttribute(_currentMetricName.toStdString(), value.toStdString());
			}
		}
		else if (name == "metric")
		{
			QString name = attributes.value("name");
			QString valueType = attributes.value("valueType");

			_currentMetricName = name;

			if (valueType == "String")
			{
				_parser.tree()->addAttributeMap(_currentMetricName.toStdString(), AttributeMap::Nominal);
			}
			else
			{
				_parser.tree()->addAttributeMap(_currentMetricName.toStdString(), AttributeMap::Numeric);
			}
		}

		return true;
	}

	if (_stack.size() == 0)
	{
		_stack.push(_parser.tree()->root());

		return true;
	}

	Q_ASSERT(_stack.top());

	Node* node = new Node();
	_stack.top()->addChild(node);

	node->setName(attributes.value("name").toStdString());
	_nodes[attributes.value("id")] = node;

	_stack.push(node);

	return true;
}

bool SoftwareSystemStrategy::endElement(const QString& namespaceURI, const QString& localName, const QString& name)
{
	if (name != "directory" && name != "file")
	{
		return true;
	}

	_stack.pop();

	return true;
}

bool SoftwareSystemStrategy::characters(const QString& characters)
{
	return true;
}
