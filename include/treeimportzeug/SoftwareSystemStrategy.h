#pragma once

#include <QStack>
#include <QHash>
#include <QString>


#include <treeimportzeug/treeimportzeug.h>
#include <treeimportzeug/TreeXmlParserStrategy.h>


namespace zeug
{

class Node;

class TREEIMPORTZEUG_API SoftwareSystemStrategy : public TreeXmlParserStrategy
{
public:
	SoftwareSystemStrategy(TreeXmlParser & parser);

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
	QString m_currentMetricName;
	QStack<Node*> m_stack;

	QHash<QString, Node*> m_nodes;
};

} // namespace zeug
