#pragma once

#ifndef TABLE_HEADER
#define TABLE_HEADER

#include <string>
#include "Column.h"

class Table {
private:
	std::string tableName;

	int size;
	Column* columns;
	int top;

	bool full() const;
	bool empty() const;
	void grow();

	void add(Column&);
	bool columnExists(std::string);
	std::string columnNames();
	std::string tableInfo();
	std::string getColumnType(int);

	std::string getTableName() const;
	void setTableName(std::string);
	int getSize() const;
	int getTop() const;

public:
	Table();
	Table(std::string);
	Table(const Table&);
	Table& operator=(const Table&);
	~Table();

	friend class TableController;
	friend class Database;
};
#endif