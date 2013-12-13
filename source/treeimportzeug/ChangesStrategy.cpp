#include <treeimportzeug/ChangesStrategy.h>

#include <QSqlRecord>

#include <treezeug/Tree.h>

namespace zeug
{

ChangesStrategy::ChangesStrategy()
: m_nextId(0)
{
}

void ChangesStrategy::createTrees()
{
    loadAttributes();
    processRevisions(executeQuery("SELECT id FROM revisions WHERE 1 ORDER BY id"));
}

void ChangesStrategy::clear()
{
    m_attributes.clear();
    m_attributeValues.clear();
    m_ids.clear();
    m_nextId = 0;
}

QSet<QString> ChangesStrategy::wantedFileSuffixes() const
{
    return QSet<QString>() << "sqlite" << "db" << "sqlite3";
}

bool ChangesStrategy::wantsToProcess(QSqlDatabase& database) const
{
    return !database.record("nodes").isEmpty()
            && !database.record("revisions").isEmpty()
            && !database.record("schema").isEmpty()
            && !database.record("schema_attrs").isEmpty();
}

void ChangesStrategy::loadAttributes()
{
	for (const QVariantMap& attributeType : executeQuery("SELECT id, type_id, name, type FROM schema_attrs WHERE 1"))
	{
		m_attributes[NodeType(attributeType["type_id"].toInt())] << Attribute(
			attributeType["name"].toString(),
			attributeType["type"].toString() == "TEXT" ? AT_Text : AT_Integer,
			attributeType["id"].toUInt()
		);
		
		m_attributeValues[attributeType["id"].toUInt()] = executeQuery("SELECT node_id, value FROM attr_" + QString::number(attributeType["id"].toUInt()));
	}
}

void ChangesStrategy::processRevisions(const QList<QVariantMap>& revisions)
{
	for (const QVariantMap& revision : revisions)
	{
		createTreeForRevision(revision["id"].toUInt());
	}
}

void ChangesStrategy::createTreeForRevision(unsigned revisionId)
{
    Tree* tree = new Tree(QString("Revision %1").arg(revisionId).toStdString());
	
	tree->addAttributeMap("id", AttributeMap::Numeric);
	tree->addAttributeMap("depth", AttributeMap::Numeric);
	
	for (const QList<Attribute>& attributes : m_attributes)
	{
		for (const Attribute& attribute : attributes)
		{
			if (attribute.name == "label")
			{
				continue;
			}
			
			tree->addAttributeMap(
				attribute.name.toStdString(),
				attribute.type == AT_Integer ? AttributeMap::Numeric : AttributeMap::Nominal
			);
		}
	}
	
	m_trees << tree;

    QHash<GeneratedId, Node*> nodes;
    QHash<DatabaseId, GeneratedId> ids;
    QHash<GeneratedId, GeneratedId> parentIds;
	
	QList<QVariantMap> rows = executeQuery("SELECT id, hash, type_id, parent_id FROM nodes WHERE revision_id = " + QString::number(revisionId) + " ORDER BY id");
    for (const QVariantMap& row : rows)
	{
        GeneratedId id = idFor(row["hash"].value<DatabaseHash>());
		nodes[id] = new Node(id);
        ids[row["id"].value<DatabaseId>()] = id;
	}
	
    for (const QVariantMap& row : rows)
	{
        parentIds[ids[row["id"].value<DatabaseId>()]] = ids[row["parent_id"].value<DatabaseId>()];
	}
	
    for (Node* node : nodes)
    {
        insertIntoTree(node, tree, nodes, parentIds);
	}
	
	for (Node* node : nodes)
	{
		node->setAttribute("id", node->id());
		node->setAttribute("depth", node->depth());
	}
	
	for (const QList<Attribute>& attributeList : m_attributes)
	{
		for (const Attribute& attribute : attributeList)
		{
			for (const QVariantMap& attributeValue : m_attributeValues[attribute.index])
			{
                if (!ids.contains(attributeValue["node_id"].toInt()))
				{
					continue;
				}
				
                Node* node = tree->getNode(ids[attributeValue["node_id"].toInt()]);
				
				Q_ASSERT(node != nullptr);
				
				if (attribute.name == "label")
				{
					node->setName(attributeValue["value"].toString().toStdString());
				}
				else
				{
					node->setAttribute(attribute.name.toStdString(), attributeValue["value"].toString().toStdString());
				}
			}
		}
	}

    tree->nodesOrderedByDepthDo([](Node* node) {
        std::sort(node->children().begin(), node->children().end(), [](Node* node1, Node* node2) {
            return node1->id() < node2->id();
        });
    });
}

void ChangesStrategy::insertIntoTree(Node* node, Tree* tree, const QHash<GeneratedId, Node*>& nodes, const QHash<GeneratedId, GeneratedId>& parentIds) const
{
	if (node->id() == 0)
	{
		tree->setRoot(node);
		
		return;
	}
	
	if (tree->getNode(node->id()))
	{
		Q_ASSERT(tree->getNode(node->id()) == node);
		
		return;
	}
	
    if (parentIds.value(node->id(), 0) <= 0)
	{
		tree->root()->addChild(node);
		
		return;
	}
	
	if (!tree->getNode(parentIds.value(node->id(), 0)))
	{
		insertIntoTree(nodes.value(parentIds.value(node->id(), 0), nullptr), tree, nodes, parentIds);
	}
	
	tree->getNode(parentIds.value(node->id(), 0))->addChild(node);
	
    //Q_ASSERT(node->tree() == tree);
}

int ChangesStrategy::idFor(long hash) const
{
	if (!m_ids.contains(hash))
	{
		m_ids[hash] = m_nextId;	
		++m_nextId;
	}
	return m_ids[hash];
}

} // namespace zeug
