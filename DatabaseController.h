#pragma once

class DatabaseController {
private:
	std::string verifyDatabaseName(std::string);
public:
	DatabaseController();
	void add(Database&, Table& const);
	void create(Database& , std::string);
	void remove(Database&, std::string);
	void renameTable(Database&, std::string, std::string);
	bool tableExists(Database&, std::string);
	void tableNames(Database& const);
};
