#include <treeimportzeug/TreeXmlParser.h>

#include <treeimportzeug/CityGMLStrategy.h>
#include <treeimportzeug/TreeStrategy.h>
#include <treeimportzeug/SoftwareSystemStrategy.h>

#include <iostream>

#include <QFileInfo>

TreeXmlParser::TreeXmlParser()
: m_tree(nullptr)
, m_strategy(nullptr)
{
    m_tree = new Tree("");
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

    parser.tree()->setName(QFileInfo(filename).baseName().toStdString());

	return parser.tree();
}

Tree* TreeXmlParser::tree()
{
	return m_tree;
}

bool TreeXmlParser::startDocument()
{
	return true;
}

bool TreeXmlParser::endDocument()
{
	if (m_strategy)
	{
		m_strategy->endDocument();
	}

	m_tree->addAttributeMap("id", AttributeMap::Numeric);
	m_tree->addAttributeMap("depth", AttributeMap::Numeric);

	m_tree->nodesDo([](Node* node) {
		node->setAttribute("id", node->id());
		node->setAttribute("depth", node->depth());
	});

	return true;
}

bool TreeXmlParser::startElement(const QString& namespaceURI, const QString& localName, const QString& name, const QXmlAttributes& attributes)
{
	if (m_strategy)
	{
		return m_strategy->startElement(namespaceURI, localName, name, attributes);
	}
	else
	{
		if (name == "tree")
		{
			m_strategy = new TreeStrategy(*this);

			return m_strategy->startDocument();
		}
		else if (name == "hpiSoftwareSystem")
		{
			m_strategy = new SoftwareSystemStrategy(*this);

			return m_strategy->startDocument();
		}
		else if (name == "hierarchy")
		{
			m_strategy = new CityGMLStrategy(*this);

			return m_strategy->startDocument();
		}
	}

	return false;
}

bool TreeXmlParser::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	if (m_strategy)
	{
		return m_strategy->endElement(namespaceURI, localName, qName);
	}

	return false;
}

bool TreeXmlParser::characters(const QString& characters)
{
	if (m_strategy)
	{
		return m_strategy->characters(characters);
	}

	return false;
}
