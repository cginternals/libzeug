#pragma once

#include <TreeXmlParserStrategy.h>

#include <QStack>
#include <QString>

class Node;

class TreeStrategy : public TreeXmlParserStrategy
{
public:
	TreeStrategy(TreeXmlParser& parser);

	virtual bool startDocument();
	virtual bool endDocument();

	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attributes);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);

	virtual bool characters(const QString& characters);
protected:
	QStack<Node*> _stack;
};
