#include <treeimportzeug/RepositoryStrategy.h>

#include <QSqlRecord>
#include <QStringList>

#include <treezeug/MutableTree.h>

namespace zeug
{

RepositoryStrategy::RepositoryStrategy()
{
}

void RepositoryStrategy::createTrees()
{
    loadMetrics();
    processRevisions(executeQuery("SELECT \"id\", \"name\", \"date\" FROM \"revisions\" WHERE 1 ORDER BY \"id\""));
}

void RepositoryStrategy::clear()
{
    m_metrics.clear();
}

QSet<QString> RepositoryStrategy::wantedFileSuffixes() const
{
    return QSet<QString>() << "sqlite" << "db" << "sqlite3";
}

bool RepositoryStrategy::wantsToProcess(QSqlDatabase& database) const
{
    return !database.record("revisions").isEmpty()
        && !database.record("nodes").isEmpty()
        && !database.record("metrics").isEmpty()
        && !database.record("metricValues").isEmpty();
}

void RepositoryStrategy::loadMetrics()
{
    for (const QVariantMap& metric : executeQuery("SELECT \"id\", \"name\", \"type\" FROM \"metrics\" WHERE 1"))
	{
        m_metrics[metric["id"].toInt()] = Metric(
            metric["name"].toString(),
            metric["type"].toString() == "integer" ? MT_Integer : MT_Text,
            metric["id"].toInt()
        );
	}
}

void RepositoryStrategy::processRevisions(const QList<QVariantMap>& revisions)
{
	for (const QVariantMap& revision : revisions)
	{
        createTreeForRevision(revision["id"].toUInt(), revision["date"].toString());
	}
}

void RepositoryStrategy::createTreeForRevision(unsigned revisionId, const QString& name)
{
    MutableTree* tree = new MutableTree(QString("Revision %1 (%2)").arg(revisionId).arg(name).toStdString());
	
	tree->addAttributeMap("id", AttributeMap::Numeric);
	tree->addAttributeMap("depth", AttributeMap::Numeric);
	
    for (const Metric& metric : m_metrics)
	{
        tree->addAttributeMap(
            metric.name.toStdString(),
            metric.type == MT_Integer ? AttributeMap::Numeric : AttributeMap::Nominal
        );
	}

    QHash<int, Node*> nodes;
	
    QList<QVariantMap> rows = executeQuery("SELECT \"id\", \"index\", \"parent\", \"label\" FROM \"nodes\" WHERE revision = " + QString::number(revisionId) + " ORDER BY \"id\"");
    QStringList ids;
    for (const QVariantMap& row : rows)
	{
        zeug::Node* node = new Node(row["index"].toInt());

        nodes[row["id"].toInt()] = node;

        ids << QString::number(row["id"].toInt());

        if (node->id() == 0)
        {
            Q_ASSERT(row["parent"].toInt() == 0);

            tree->setRoot(node);
        }
        else
        {
            Q_ASSERT(row["parent"].toInt() >= 1);

            nodes[row["parent"].toInt()]->addChild(node);
        }

        node->setName(row["label"].toString().toStdString());
        node->setAttribute("id", node->id());
        node->setAttribute("depth", node->depth());
	}

    QList<QVariantMap> metricValues = executeQuery("SELECT \"node\", \"metric\", \"value\" FROM \"metricValues\" WHERE \"node\" IN (" + ids.join(", ") + ")");
    for (const QVariantMap& row : metricValues)
    {
        nodes[row["node"].toInt()]->setAttribute(m_metrics[row["metric"].toInt()].name.toStdString(), row["value"].toString().toStdString());
    }

    tree->nodesOrderedByDepthDo([](Node* node) {
        std::sort(node->children().begin(), node->children().end(), [](Node* node1, Node* node2) {
            return node1->id() < node2->id();
        });
    });

    tree->renormalizeAttributesForLeaves();

    m_trees << tree->copy();
}

} // namespace zeug

