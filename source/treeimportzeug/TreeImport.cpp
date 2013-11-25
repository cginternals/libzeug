#include <treeimportzeug/TreeImport.h>

#include <QFileInfo>

#include <treeimportzeug/TreeXmlParser.h>
#include <treeimportzeug/TreeSqliteParser.h>

namespace zeug
{

QList<QString> TreeImport::s_allowedFileSuffixes = QList<QString>() << "xml" << "db" << "sqlite3";

const QList<QString>& TreeImport::allowedFileSuffixes()
{
	return s_allowedFileSuffixes;
}

QList<Tree*> TreeImport::loadFromFile(const QString& filename)
{
	QFileInfo fileinfo(filename);

	if (!fileinfo.exists() || !fileinfo.isFile() || !s_allowedFileSuffixes.contains(fileinfo.suffix()))
	{
		return QList<Tree*>();
	}
	
	QList<zeug::Tree*> trees;

	if (fileinfo.suffix() == "xml")
	{
		trees = zeug::TreeXmlParser::createTreesFromFile(filename);
	}
	else if (fileinfo.suffix() == "db" || fileinfo.suffix() == "sqlite3")
	{
		trees = zeug::TreeSqliteParser::createTreesFromDatabase(filename);
	}
	
	return trees;
}

} // namespace zeug
