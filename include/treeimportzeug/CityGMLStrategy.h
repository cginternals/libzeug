#pragma once

#include <QString>

#include <treeimportzeug/treeimportzeug.h>
#include <treeimportzeug/TreeXmlParserStrategy.h>

namespace zeug
{

class TREEIMPORTZEUG_API CityGMLStrategy : public TreeXmlParserStrategy
{
	enum InformationType 
	{
		None
		,   Label
		,   ParentId
		,   Size
	};
public:
    CityGMLStrategy();
protected:
	int m_id;
	QString m_label;

	int m_parentId;
	int m_size;

	InformationType m_nextInformation;
	
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
