#pragma once
#include "Table.h"
#include <iostream>
#include <algorithm>

class TableController {
private:
	std::string verifyTableName(std::string);
public:
	TableController();
	Table createTable(std::string);
	void addColumn(Table&, std::string, std::string);
	void describe(Table& const);
	void columns(Table& const);
	void rename(Table&, std::string);
};