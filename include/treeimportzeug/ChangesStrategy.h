#pragma once

#include <QList>
#include <QHash>

#include <treeimportzeug/treeimportzeug.h>
#include <treeimportzeug/TreeSqliteParserStrategy.h>

namespace zeug
{

class Tree;
class Node;

class TREEIMPORTZEUG_API ChangesStrategy : public TreeSqliteParserStrategy
{
public:
	ChangesStrategy();

	virtual QSet<QString> wantedFileSuffixes() const override;
protected:
	typedef int GeneratedId;
	typedef int DatabaseId;
	typedef int DatabaseHash;

	virtual void createTrees() override;
	virtual void clear() override;
	virtual bool wantsToProcess(QSqlDatabase& database) const override;

	void loadAttributes();

	void processRevisions(const QList<QVariantMap> & revisions);

	void createTreeForRevision(unsigned revisionId);

	int idFor(long hash) const;
	void insertIntoTree(
	Node * node
	,   Tree * tree
	,   const QHash<GeneratedId, Node*> & nodes
	,   const QHash<GeneratedId, GeneratedId> & parentIds) const;
protected:
	enum NodeType 
	{
		NT_Directory    = 1
		,   NT_File         = 2
	};

	enum AttributeType 
	{
		AT_Text
		,   AT_Integer
	};

	struct Attribute 
	{
		Attribute(
		const QString & name
		,   AttributeType type
		,   unsigned index)
		:   name(name)
		,   type(type)
		,   index(index)
		{
		};

		QString name;
		AttributeType type;
		unsigned index;
	};
protected:
	QList<Tree*> m_trees;
	QHash<NodeType, QList<Attribute>> m_attributes;
	QHash<unsigned, QList<QVariantMap>> m_attributeValues;

	mutable QHash<DatabaseHash, GeneratedId> m_ids;
	mutable GeneratedId m_nextId;
};

} // namespace zeug
