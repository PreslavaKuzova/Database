#pragma once

#ifndef DATABASE_CONTROLLER_HEADER
#define DATABASE_CONTROLLER_HEADER

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "File.h"
#include "Column.h"
#include "Table.h"
#include "Database.h"
#include "FileController.h"
#include "ColumnController.h"
#include "TableController.h"

class DatabaseController {
private:
	std::string toLowercase(std::string);
	std::string getNameLoadedTable(std::string);
	std::vector<std::string> parseString(std::string, char);
public:
	DatabaseController();
	void load(Database&, std::string);
	void add(Database&, Table& const, File& const);
	void create(Database&, std::string, File& const);
	void remove(Database&, std::string);
	void renameTable(Database&, std::string, std::string);
	bool tableExists(Database&, std::string);
	void showTables(Database& const);
	void describe(Database& const, std::string);
	Table& returnTableByName(Database& const, std::string);
	File& returnFileByTableName(Database& const, std::string);
	void print(Database& const, std::string);
	
	//saves the file into a .txt file
	void save();
	void select();
	void addColumn(Database&, std::string, std::string, std::string);
	void update(Database&, std::string, int, std::string, int, std::string);
	void deleteRows(Database&, std::string, int, std::string);
	void insertRow(Database&, std::string);
	void count(Database& const, std::string, int, std::string);
};

#endif