#pragma once
#include <string>
#include "Column.h"

class ColumnController {
private:
	std::string verifyColumnName(std::string);
	std::string verifyColumnType(std::string);
public:
	ColumnController();
	Column createColumn(std::string, std::string, bool = false);
	std::string getColumnInfo(Column&);
	std::string getColumnName(Column& const);
};
