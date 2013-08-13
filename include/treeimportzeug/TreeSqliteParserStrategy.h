#pragma once

class TreeSqliteParser;

class TreeSqliteParserStrategy
{
public:
	TreeSqliteParserStrategy(TreeSqliteParser& parser);
	
	virtual void process() = 0;
protected:
	TreeSqliteParser& _parser;
};
