#pragma once

class TreeSqliteParser;

class TreeSqliteParserStrategy
{
public:
	TreeSqliteParserStrategy(TreeSqliteParser& parser);
	
	virtual void processOne() = 0;
	virtual void processMultiple() = 0;
protected:
	TreeSqliteParser& _parser;
};
