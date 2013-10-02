#pragma once

#include <treeimportzeug/TreeSqliteParserStrategy.h>

#include <treezeug/Tree.h>

#include <QList>

class ChangesStrategy : public TreeSqliteParserStrategy
{
public:
	ChangesStrategy(TreeSqliteParser& parser);
	
	virtual void processOne();
	virtual void processMultiple();
protected:
    typedef int GeneratedId;
    typedef int DatabaseId;
    typedef int DatabaseHash;
	enum NodeType {
		NT_Directory = 1,
		NT_File = 2
	};
	enum AttributeType {
		AT_Text,
		AT_Integer
	};
	struct Attribute {
		Attribute(const QString& name, AttributeType type, unsigned index)
		: name(name)
		, type(type)
		, index(index)
		{
		};
		
		QString name;
		AttributeType type;
		unsigned index;
	};
	
	QList<Tree*> _trees;
	QHash<NodeType, QList<Attribute>> _attributes;
	QHash<unsigned, QList<QVariantMap>> _attributeValues;
    mutable QHash<DatabaseHash, GeneratedId> _ids;
    mutable GeneratedId _nextId;
	
	void loadAttributes();
	void processRevisions(const QList<QVariantMap>& revisions);
	void createTreeForRevision(unsigned revisionId);
	void transferTrees();
	int idFor(long hash) const;
    void insertIntoTree(Node* node, Tree* tree, const QHash<GeneratedId, Node*>& nodes, const QHash<GeneratedId, GeneratedId>& parentIds) const;
};
