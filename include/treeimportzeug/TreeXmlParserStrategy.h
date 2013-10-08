#pragma once

#include <QtXml/QtXml>
#include <QString>

#include <treeimportzeug/treeimportzeug.h>

namespace zeug
{

class TreeXmlParser;

class TREEIMPORTZEUG_API TreeXmlParserStrategy
{
public:
	TreeXmlParserStrategy(TreeXmlParser & parser);

	virtual bool startDocument() = 0;
	virtual bool endDocument() = 0;

	virtual bool startElement(
        const QString & namespaceURI
    ,   const QString & localName
    ,   const QString & qName
    ,   const QXmlAttributes & attributes) = 0;

	virtual bool endElement(
        const QString & namespaceURI
    ,   const QString & localName
    ,   const QString & qName) = 0;

	virtual bool characters(const QString & characters) = 0;

protected:
	TreeXmlParser & m_parser;
};

} // namespace zeug
