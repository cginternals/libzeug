
#include <treeimportzeug/TreeXmlParserStrategy.h>

#include <QFile>
#include <QFileInfo>

#include <treezeug/Tree.h>

namespace zeug
{

TreeXmlParserStrategy::TreeXmlParserStrategy()
: m_inWantsToProcess(false)
, m_wantsToProcess(false)
, m_tree(nullptr)
{
}

void TreeXmlParserStrategy::initialize(const QString& filename)
{
	m_filename = filename;
}

bool TreeXmlParserStrategy::wantsToProcess()
{
	if (!QFileInfo(m_filename).exists() || QFileInfo(m_filename).isFile())
	{
		return false;
	}
	
	QFile file(m_filename);
	QXmlSimpleReader xmlReader;
	
	xmlReader.setContentHandler(this);
	xmlReader.setErrorHandler(this);
	
	m_inWantsToProcess = true;

	QXmlInputSource source(&file);
	xmlReader.parse(&source);
	
	m_inWantsToProcess = false;
	
	return m_wantsToProcess;
}

QList<Tree*> TreeXmlParserStrategy::process()
{
	QFile file(m_filename);
	QXmlSimpleReader xmlReader;
	
	xmlReader.setContentHandler(this);
	xmlReader.setErrorHandler(this);
	
	QXmlInputSource source(&file);
	xmlReader.parse(&source);

    return QList<Tree*>() << m_tree;
}

void TreeXmlParserStrategy::cleanup()
{
	clear();
	
	m_inWantsToProcess = false;
	m_wantsToProcess = false;
	
	delete m_tree;
	m_tree = nullptr;
}

bool TreeXmlParserStrategy::startDocument()
{
	start();
	
	return true;
}

bool TreeXmlParserStrategy::endDocument()
{
	m_tree->addAttributeMap("id", AttributeMap::Numeric);
	m_tree->addAttributeMap("depth", AttributeMap::Numeric);

	m_tree->nodesDo([](Node * node) {
		node->setAttribute("id", node->id());
		node->setAttribute("depth", node->depth());
	});
	
	finish();

    return true;
}

bool TreeXmlParserStrategy::startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & attributes)
{
	if (m_inWantsToProcess)
	{
		m_wantsToProcess = wantsToProcess(qName, attributes);
		
		return false;
	}
	else
	{
		return startElement(qName, attributes);
	}
}

bool TreeXmlParserStrategy::endElement(const QString & namespaceURI, const QString & localName, const QString & qName)
{
	if (m_inWantsToProcess)
	{
		return true;
	}
	else
	{
		return endElement(qName);
	}
}

bool TreeXmlParserStrategy::characters(const QString & characterString)
{
	if (m_inWantsToProcess)
	{
		return true;
	}
	else
	{
        return handleCharacters(characterString);
	}
}

} // namespace zeug
