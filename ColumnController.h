#pragma once

#ifndef COLUMN_CONTROLLER_HEADER
#define COLUMN_CONTROLLER_HEADER

#include <string>
#include "Column.h"

class ColumnController {
private:
	std::string verifyColumnName(std::string);
	std::string verifyColumnType(std::string);
	
	ColumnController();
	Column createColumn(std::string, std::string, bool = false);
	std::string getColumnInfo(Column&);
	std::string getColumnName(Column& const);
public:
	friend class TableController;
	friend class DatabaseController;
};

#endif