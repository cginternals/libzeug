#pragma once

#include <QString>
#include <QList>

#include <treezeug/Tree.h>

#include <treeimportzeug/treeimportzeug.h>

namespace zeug
{

class TREEIMPORTZEUG_API TreeImport
{
public:
	static QList<Tree*> loadFromFile(const QString& filename);
	static const QList<QString>& allowedFileSuffixes();
protected:
	static QList<QString> s_allowedFileSuffixes;
private:
	TreeImport();
};

} // namespace zeug
