#include "Database.h"

Database::Database(std::string name): databaseName(name), size(1), top(-1) {
	tables = new Table[0];
}

Database::Database(const Database& database): 
	databaseName(database.databaseName), size(database.size), top(database.top) {
	tables = new Table[size];
	for (int i = 0; i <= top; i++) {
		tables[i] = database.tables[i];
	}
}

Database& Database::operator=(const Database& database){
	if (this != &database) {
		this->databaseName = database.databaseName;
		this->size = database.size;
		this->top = database.top;
		delete[] tables;

		tables = new Table[size];

		for (int i = 0; i <= top; i++) {
			tables[i] = database.tables
[i];
		}
	}
	return *this;
}

Database::~Database() {
	delete[] tables;
}

void Database::addTable(Table& table) {
	if (this->full() || this->empty()) {
		this->grow();
	}

	tables[++top] = table;
}

//add a check in the CONTROLLER whether the database is EMPTY and whether the TABLE EXISTS
void Database::removeTable(std::string tableName) {
	int j = 0;
	Table* array = new Table[this->size];
	for (int i = 0; i <= top; i++) {
		if (tableName.compare(this->tables[i].getTableName())) {
			array[j] = this->tables[i];
			j++;
		}
	}
	this->tables = array;
}

bool Database::tableExists(std::string tableName) {
	for (int i = 0; i <= top; i++) {
		if (!tableName.compare(this->tables[i].getTableName())) {
			return true;
		}
	}
	return false;
}

std::string Database::tableNames() {
	std::string stringTables = "";
	for (int i = 0; i <= this->top; i++) {
		stringTables += this->tables[i].getTableName() + " ";
	}
	return stringTables;
}

bool Database::full() const {
	return this->top == this->size - 1;
}

bool Database::empty() const {
	return this->top == -1;
}

void Database::grow() {
	Table* array = new Table[2 * size];

	for (int i = 0; i <= top; i++) {
		array[i] = tables[i];
	}

	delete[] tables;

	tables = array;
	size *= 2;
}

std::string Database::getName() const {
	return this->databaseName;
}

void Database::setName(std::string name) {
	this->databaseName = name;

}

int Database::getSize() const {
	return this->size;
}

int Database::getTop() const {
	return this->top;
}