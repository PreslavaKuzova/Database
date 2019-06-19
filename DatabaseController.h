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

	//when working with file is added
	//maybe work with another controller and write the implementation there
	void print(Database& const);
	void load();
	void save();
	void select();
	void update();
	void deleteRow();
	void insert();
	void innerJoin();
	void count();
	void aggregate();
};
