#pragma once

#ifndef TABLE_CONTROLLER_HEADER
#define TABLE_CONTROLLER_HEADER

#include "Table.h"
#include "Column.h"
#include "ColumnController.h"
#include <iostream>
#include <algorithm>

class TableController {
private:
	std::string toLowercase(std::string);

	TableController();
	Table createTable(std::string);
	void addColumn(Table&, Column& const);
	void createColumn(Table&, std::string, std::string);
	bool columnExists(Table&, std::string);
	void tableInfo(Table& const);
	void columns(Table& const);
	void rename(Table&, std::string);
	std::string getName(Table& const);
	std::string getColumnTypeFromIndex(Table& const, int);
	bool columnExistsByIndex(Table& const, int);
public:


	friend class DatabaseController;
};

#endif