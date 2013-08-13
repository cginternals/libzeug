#pragma once

#include <TreeSqliteParserStrategy.h>

class ChangesStrategy : public TreeSqliteParserStrategy
{
public:
	ChangesStrategy(TreeSqliteParser& parser);
	
	virtual void processOne();
	virtual void processMultiple();
};
