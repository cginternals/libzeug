#include <TreeXmlParser.h>

#include <CityGMLStrategy.h>
#include <TreeStrategy.h>
#include <SoftwareSystemStrategy.h>

#include <iostream>

TreeXmlParser::TreeXmlParser()
: _tree(nullptr)
, _strategy(nullptr)
{
	_tree = new Tree();
}

Tree* TreeXmlParser::createTreeFromFile(const QString& filename)
{
	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly))
	{
		std::cout << "could not open file " << filename.toStdString();
		return nullptr;
	}

	QXmlSimpleReader xmlReader;
	QXmlInputSource* source = new QXmlInputSource(&file);

	TreeXmlParser parser;

	xmlReader.setContentHandler(&parser);
	xmlReader.setErrorHandler(&parser);

	if (!xmlReader.parse(source))
	{
		return nullptr;
	}

	return parser.tree();
}

Tree* TreeXmlParser::tree()
{
	return _tree;
}

bool TreeXmlParser::startDocument()
{
	return true;
}

bool TreeXmlParser::endDocument()
{
	if (_strategy)
	{
		_strategy->endDocument();
	}

	_tree->addAttributeMap("id", AttributeMap::Numeric);
	_tree->addAttributeMap("depth", AttributeMap::Numeric);

	_tree->nodesDo([](Node* node) {
		node->setAttribute("id", node->id());
		node->setAttribute("depth", node->depth());
	});

	return true;
}

bool TreeXmlParser::startElement(const QString& namespaceURI, const QString& localName, const QString& name, const QXmlAttributes& attributes)
{
	if (_strategy)
	{
		return _strategy->startElement(namespaceURI, localName, name, attributes);
	}
	else
	{
		if (name == "tree")
		{
			_strategy = new TreeStrategy(*this);

			return _strategy->startDocument();
		}
		else if (name == "hpiSoftwareSystem")
		{
			_strategy = new SoftwareSystemStrategy(*this);

			return _strategy->startDocument();
		}
		else if (name == "hierarchy")
		{
			_strategy = new CityGMLStrategy(*this);

			return _strategy->startDocument();
		}
	}

	return false;
}

bool TreeXmlParser::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	if (_strategy)
	{
		return _strategy->endElement(namespaceURI, localName, qName);
	}

	return false;
}

bool TreeXmlParser::characters(const QString& characters)
{
	if (_strategy)
	{
		return _strategy->characters(characters);
	}

	return false;
}
