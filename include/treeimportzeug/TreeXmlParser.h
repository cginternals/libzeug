#pragma once

#include <QtXml/QXmlDefaultHandler>
#include <QString>

#include <treezeug/Tree.h>
#include <treeimportzeug/treeimportzeug.h>

namespace zeug
{

class TreeXmlParserStrategy;

class TREEIMPORTZEUG_API TreeXmlParser : public QXmlDefaultHandler
{
public:
	TreeXmlParser();
	
	static Tree * createTreeFromFile(const QString& filename);

	Tree * tree();

protected:
    virtual bool startDocument();
	virtual bool endDocument();

	virtual bool startElement(
        const QString & namespaceURI
    ,   const QString & localName
    ,   const QString & qName
    ,   const QXmlAttributes & attributes);

	virtual bool endElement(
        const QString & namespaceURI
    ,   const QString & localName
    ,   const QString & qName);

	virtual bool characters(const QString & characters);

protected:
	Tree * m_tree;
	TreeXmlParserStrategy * m_strategy;
};

} // namespace zeug
