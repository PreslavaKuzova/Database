#pragma once

class DatabaseController {
private:
	std::string toLowercase(std::string);
public:
	DatabaseController();
	void add(Database&, Table& const);
	void create(Database&, std::string);
	void remove(Database&, std::string);
	void renameTable(Database&, std::string, std::string);
	bool tableExists(Database&, std::string);
	void showTables(Database& const);
	void describe(Database& const, std::string);
	Table& returnTableByName(Database& const, std::string);

	//we should only give the name to the table that has to be print
	void print(Database& const, std::string);
};