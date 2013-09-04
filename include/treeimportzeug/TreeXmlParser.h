#pragma once

#include <QtXml/QXmlDefaultHandler>
#include <QString>

#include <treezeug/Tree.h>

class TreeXmlParserStrategy;

class TreeXmlParser : public QXmlDefaultHandler
{
public:
	TreeXmlParser();
	
	static Tree* createTreeFromFile(const QString& filename);

	Tree* tree();
protected:
	Tree* _tree;
	TreeXmlParserStrategy* _strategy;

	virtual bool startDocument();
	virtual bool endDocument();

	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attributes);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);

	virtual bool characters(const QString& characters);
};
