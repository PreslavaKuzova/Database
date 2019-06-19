#include "Table.h"
#include "Column.h"

Table::Table(): tableName(""), size(0), top(-1){
	columns = new Column[0];
}

Table::Table(std::string tableName): tableName(tableName), size(1), top(-1) {
	columns = new Column[0];
}

Table::Table(const Table& table): 
	tableName(table.tableName), size(table.size), top(table.top) {
	columns = new Column[size];
	for (int i = 0; i <= top; i++){
		columns[i] = table.columns[i];
	}
}

Table& Table::operator=(const Table& table) {
	if (this != &table) {
		this->tableName = table.tableName;
		this->size = table.size;
		this->top = table.top;
		delete[] columns;
		
		columns = new Column[size];
		
		for (int i = 0; i <= top; i++) {
			columns[i] = table.columns[i];
		}
	}
	return *this;
}

Table::~Table() {
	delete[] columns;
}

void Table::add(Column& column) {
	if (this->full() || this->empty()) {
		this->grow();
	}

	columns[++top] = column;
}

bool Table::columnExists(std::string name) {
	for (int i = 0; i <= this->top; i++) {
		if (!name.compare(this->columns[i].getColumnName())) {
			return true;
		}
	}
	return false;
}

std::string Table::columnNames() {
	std::string stringColumns = "";
	for (int i = 0; i <= this->top; i++) {
		stringColumns += this->columns[i].getColumnName() + " ";
	}
	return stringColumns;
}

std::string Table::tableInfo() {
	std::string description = "";
	for (int i = 0; i <= top; i++) {
		description += this->columns[i].getColumnName() + " " + this->columns[i].getType() + "\n";
	}
	return description;
}

bool Table::full() const {
	return this->top == this->size - 1;
}

bool Table::empty() const {
	return this->top == -1;
}

void Table::grow() {
	Column* array = new Column[2 * size];

	for (int i = 0; i <= top; i++) {
		array[i] = columns[i];
	}
	
	delete[] columns;
	
	columns = array;
	size *= 2;
}

std::string Table::getTableName() const {
	return this->tableName;
}

void Table::setTableName(std::string name) {
	this->tableName = name;
}

int Table::getSize() const {
	return this->size;
}

int Table::getTop() const {
	return this->top;
}
