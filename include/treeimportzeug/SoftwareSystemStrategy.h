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
	SoftwareSystemStrategy();
protected:
	QString m_currentMetricName;
	QStack<Node*> m_stack;

	QHash<QString, Node*> m_nodes;
	
    QSet<QString> wantedFileSuffixes() const override;
	virtual void clear() override;
	virtual bool wantsToProcess(const QString& tagName, const QXmlAttributes & attributes) const override;
	virtual void start() override;
	virtual void finish() override;
	virtual bool startElement(const QString & name, const QXmlAttributes & attributes) override;
	virtual bool endElement(const QString & name) override;
    virtual bool handleCharacters(const QString & characters) override;
};

} // namespace zeug
