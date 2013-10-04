#pragma once

#include <treeimportzeug/TreeXmlParserStrategy.h>

#include <QStack>
#include <QHash>
#include <QString>

class Node;

class SoftwareSystemStrategy : public TreeXmlParserStrategy
{
public:
	SoftwareSystemStrategy(TreeXmlParser& parser);

	virtual bool startDocument();
	virtual bool endDocument();

	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attributes);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);

	virtual bool characters(const QString& characters);
protected:
	QString _currentMetricName;
	QStack<Node*> _stack;
	QHash<QString, Node*> m_nodes;
};
