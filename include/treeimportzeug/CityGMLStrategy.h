#pragma once

#include <QString>

#include <treeimportzeug/treeimportzeug.h>
#include <treeimportzeug/TreeXmlParserStrategy.h>

namespace zeug
{

class TREEIMPORTZEUG_API CityGMLStrategy : public TreeXmlParserStrategy
{
public:
    enum InformationType 
    {
		None
    ,   Label
    ,   ParentId
    ,   Size
	};

public:
	CityGMLStrategy(TreeXmlParser & parser);

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
	int m_id;
	QString m_label;

    int m_parentId;
	int m_size;

	InformationType m_nextInformation;
};

} // namespace zeug
