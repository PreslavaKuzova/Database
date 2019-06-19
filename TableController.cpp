#include "TableController.h"
#include "ColumnController.h"

TableController::TableController() {
}

Table TableController::createTable(std::string name) {
	Table table(this->verifyTableName(name));
	return table;
}

std::string TableController::verifyTableName(std::string name) {
	//here we use a library function to convert the name to lowercase
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return name;
}

void TableController::addColumn(Table& table, std::string name, std::string type) {
	Column column(ColumnController().createColumn(name, type));
	table.add(column);
	std::cout << "Successfully added new column to table " << table.getTableName() << ".\n";
}

void TableController::describe(Table& const table) {
	if (!table.empty()) {
		std::cout << "Table " + table.getTableName() +" contains the following columns with the type showed:\n";
		std::cout << table.tableInfo();
	} else {
		std::cout << "Sorry, nothing to show here. Table " + table.getTableName() +" is empty.\n";
	}	
}

void TableController::columns(Table& const table) {
	if (!table.empty()) {
		std::cout << "Table " << table.getTableName() << " contains columns with the following names:\n";
		std::cout << table.columnNames() << std::endl;
	} else {
		std::cout << "Sorry, nothing to show here. Table " + table.getTableName() + " is empty.\n";
	}
}

//there must be a check whether another table in the database has such a name
//this must be done in the DatabaseController
void TableController::rename(Table& table, std::string name) {
	table.setTableName(name);
}