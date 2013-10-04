#pragma once

#include <treeimportzeug/TreeXmlParserStrategy.h>

#include <QString>

class CityGMLStrategy : public TreeXmlParserStrategy
{
public:
	enum InformationType {
		None,
		Label,
		ParentId,
		Size
	};

	CityGMLStrategy(TreeXmlParser& parser);

	virtual bool startDocument();
	virtual bool endDocument();

	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attributes);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);

	virtual bool characters(const QString& characters);
protected:
	int m_id;
	QString _label;
	int _parentId;
	int _size;
	InformationType _nextInformation;
};
