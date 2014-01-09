
#include <treeimportzeug/TreeXmlParserStrategy.h>

#include <QFile>
#include <QFileInfo>

#include "MutableTree.h"

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
    QFileInfo info(m_filename);
    if (!info.exists() || !info.isFile())
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

    return QList<Tree*>() << m_tree->copy();
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
    if (!m_inWantsToProcess)
    {
        m_tree = new MutableTree(QFileInfo(m_filename).baseName().toStdString());

        start();
    }
	
	return true;
}

bool TreeXmlParserStrategy::endDocument()
{
    if (!m_inWantsToProcess)
    {
        m_tree->addAttributeMap("id", AttributeMap::Numeric);
        m_tree->addAttributeMap("depth", AttributeMap::Numeric);

        m_tree->nodesDo([](Node * node) {
            node->setAttribute("id", node->id());
            node->setAttribute("depth", node->depth());
        });

        finish();
    }

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
