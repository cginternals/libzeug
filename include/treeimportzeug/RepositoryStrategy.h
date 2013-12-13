#pragma once

#include <QList>
#include <QHash>

#include <treeimportzeug/treeimportzeug.h>
#include <treeimportzeug/TreeSqliteParserStrategy.h>

namespace zeug
{

class Tree;
class Node;

class TREEIMPORTZEUG_API RepositoryStrategy : public TreeSqliteParserStrategy
{
public:
    RepositoryStrategy();

	virtual QSet<QString> wantedFileSuffixes() const override;
protected:
	virtual void createTrees() override;
	virtual void clear() override;
	virtual bool wantsToProcess(QSqlDatabase& database) const override;

    void loadMetrics();

	void processRevisions(const QList<QVariantMap> & revisions);

    void createTreeForRevision(unsigned revisionId, const QString& name);
protected:
    enum MetricType
	{
        MT_None
        ,   MT_Text
        ,   MT_Integer
	};

    struct Metric
	{
        Metric()
        :   type(MT_None)
        ,   index(-1)
        {
        }

        Metric(
		const QString & name
        ,   MetricType type
        ,   int index)
		:   name(name)
		,   type(type)
		,   index(index)
		{
        }

		QString name;
        MetricType type;
        int index;
	};
protected:
    QHash<int, Metric> m_metrics;
};

} // namespace zeug
