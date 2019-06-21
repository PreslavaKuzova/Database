#include "Database.h"

Database::Database(std::string name) : databaseName(name), size(1), top(-1) {
	tables = new Table[0];
	files = new File[0];
}

Database::Database(const Database& database) :
	databaseName(database.databaseName), size(database.size), top(database.top) {
	tables = new Table[size];
	files = new File[size];
	for (int i = 0; i <= top; i++) {
		tables[i] = database.tables[i];
		files[i] = database.files[i];
	}
}

Database& Database::operator=(const Database& database) {
	if (this != &database) {
		this->databaseName = database.databaseName;
		this->size = database.size;
		this->top = database.top;
		
		delete[] tables;
		delete[] files;
		
		tables = new Table[size];
		files = new File[size];

		for (int i = 0; i <= top; i++) {
			tables[i] = database.tables[i];
			files[i] = database.files[i];
		}
	}
	return *this;
}

Database::~Database() {
	delete[] tables;
	delete[] files;
}

void Database::addTable(Table& table, File& file) {
	if (this->full() || this->empty()) {
		this->grow();
	}

	this->top++;
	
	this->tables[this->top] = table;
	this->files[this->top] = file;
}

void Database::removeTable(std::string tableName) {
	int j = 0;
	
	Table* tableArray = new Table[this->size];
	File* fileArray = new File[this->size];

	for (int i = 0; i <= top; i++) {
		if (tableName.compare(this->tables[i].getTableName())) {
			tableArray[j] = this->tables[i];
			fileArray[j] = this->files[i];
			j++;
		}
	}
	this->tables = tableArray;
	this->files = fileArray;
	this->top--;
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
	Table* tableArray = new Table[2 * size];
	File* fileArray = new File[2 * size];

	for (int i = 0; i <= top; i++) {
		tableArray[i] = this->tables[i];
		fileArray[i] = this->files[i];
	}

	delete[] this->tables;
	delete[] this->files;

	this->tables = tableArray;
	this->files = fileArray;
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