#pragma once
#include <string>
#include "Table.h"

class Database {
private:
	std::string databaseName;

	int size;
	Table* tables;
	int top;

	bool full() const;
	bool empty() const;
	void grow();

	void addTable(Table&);
	void removeTable(std::string);
	bool tableExists(std::string);
	std::string tableNames();

	std::string getName() const;
	void setName(std::string);
	int getSize() const;
	int getTop() const;

public:
	Database(std::string);
	Database(const Database&);
	Database& operator=(const Database&);
	~Database();

	friend class DatabaseController;
};
