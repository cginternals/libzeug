#pragma once

#include <QtXml/QtXml>
#include <QtXml/QXmlDefaultHandler>
#include <QString>

#include <treeimportzeug/treeimportzeug.h>
#include <treeimportzeug/TreeParserStrategy.h>

namespace zeug
{

class Tree;

class TREEIMPORTZEUG_API TreeXmlParserStrategy : public TreeParserStrategy, public QXmlDefaultHandler
{
public:
	TreeXmlParserStrategy();

	virtual void initialize(const QString& filename) override;
	virtual bool wantsToProcess() override;
	virtual QList<Tree*> process() override;
	virtual void cleanup() override;

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
	QString m_filename;
	bool m_inWantsToProcess;
	bool m_wantsToProcess;
	Tree * m_tree;

	virtual void clear() = 0;
	virtual bool wantsToProcess(const QString& tagName, const QXmlAttributes & attributes) const = 0;
	virtual bool startElement(const QString & name, const QXmlAttributes & attributes) = 0;
	virtual bool endElement(const QString & name) = 0;
    virtual bool handleCharacters(const QString & characterString) = 0;
	virtual void start() = 0;
	virtual void finish() = 0;
};

} // namespace zeug
