#include "TableController.h"
#include "ColumnController.h"

TableController::TableController() {
}

//creates a table with a given name
Table TableController::createTable(std::string name) {
	Table table(this->verifyTableName(name));
	return table;
}

//converts the name to lowercase
std::string TableController::verifyTableName(std::string name) {
	//here we use a library function to convert the name to lowercase
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return name;
}

//adds an already created column to the list
void TableController::addColumn(Table& table, Column& const column) {
	if (table.columnExists(ColumnController().getColumnName(column))) {
		std::cout << "Sorry. There is already a column with such a name in the table "
			<< table.getTableName() << std::endl;
	} else {
		table.add(column);
	}	
}

//creates a column and then adds it to the list
void TableController::createColumn(Table& table, std::string name, std::string type) {
	if (table.columnExists(name)) {
		std::cout << "Sorry. There is already a column with name " << name << " in table " 
			<< table.getTableName() << ".\n";
	} else {
		Column column(ColumnController().createColumn(name, type));
		table.add(column);
		std::cout << "Successfully added new column to table " << table.getTableName() << ".\n";
	}
}

//gives the information about the columns in the table (name and type)
void TableController::describe(Table& const table) {
	if (!table.empty()) {
		std::cout << "Table " + table.getTableName() +" contains the following columns with the type showed:\n";
		std::cout << table.tableInfo();
	} else {
		std::cout << "Sorry, nothing to show here. Table " + table.getTableName() +" is empty.\n";
	}	
}

//gives information about the names of the columns in the table
void TableController::columns(Table& const table) {
	if (!table.empty()) {
		std::cout << "Table " << table.getTableName() << " contains columns with the following names:\n";
		std::cout << table.columnNames() << std::endl;
	} else {
		std::cout << "Sorry, nothing to show here. Table " + table.getTableName() + " is empty.\n";
	}
}

//renames a table
void TableController::rename(Table& table, std::string name) {
	table.setTableName(name);
}

//returns the name of the table
std::string TableController::getName(Table& const table) {
	return table.getTableName();
}