#include "TableController.h"

TableController::TableController() {
}

//creates a table with a given name
Table TableController::createTable(std::string name) {
	Table table(this->toLowercase(name));
	return table;
}

//converts the name to lowercase
std::string TableController::toLowercase(std::string name) {
	//here we use a library function to convert the name to lowercase
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return name;
}

//adds an already created column to the list
void TableController::addColumn(Table& table, Column& const column) {
	if (table.columnExists(ColumnController().getColumnName(column))) {
		std::cout << "Sorry. There is already a column with such a name in the table "
			<< table.getTableName() << std::endl;
	}
	else {
		table.add(column);
	}
}

//returns either true or false depending whether column with such name has been added to the table
bool TableController::columnExists(Table& table, std::string columnName) {
	return table.columnExists(columnName);
}

//creates a column and then adds it to the list
void TableController::createColumn(Table& table, std::string name, std::string type) {
	if (table.columnExists(this->toLowercase(name))) {
		std::cout << "Sorry. There is already a column with name " << name << " in table "
			<< table.getTableName() << ".\n";
	}
	else {
		Column column(ColumnController().createColumn(name, type));
		table.add(column);
		std::cout << "Successfully added new column to table " << table.getTableName() << ".\n";
	}
}

//gives the information about the columns in the table (name and type)
void TableController::tableInfo(Table& const table) {
	if (!table.empty()) {
		std::cout << "Table " + table.getTableName() + " contains the following columns with the type showed:\n";
		std::cout << table.tableInfo();
	} else {
		std::cout << "Sorry, nothing to show here. Table " + table.getTableName() + " is empty.\n";
	}
}

//gives information about the names of the columns in the table
std::string TableController::columns(Table& const table) {
	if (!table.empty()) {
		return table.columnNames();
	} else {
		std::cout << "Sorry, nothing to show here. Table " + table.getTableName() + " is empty.\n";
		return "";
	}
}

//returns a string containing the types of the columns
std::string TableController::types(Table& const table) {
	if (!table.empty()) {
		return table.columnTypes();
	} else {
		std::cout << "Sorry, nothing to show here. Table " + table.getTableName() + " is empty.\n";
		return "";
	}
}

//renames a table
void TableController::rename(Table& table, std::string name) {
	table.setTableName(this->toLowercase(name));
}

//returns the name of the table
std::string TableController::getName(Table& const table) {
	return table.getTableName();
}

//returns the type of the column given
std::string TableController::getColumnTypeFromIndex(Table& const table, int columnNumber) {
	std::string type = table.getColumnType(columnNumber);
	return type;
}

//returns whether column with such index exists 
bool TableController::columnExistsByIndex(Table& const table, int columnNumber) {
	return columnNumber <= table.getTop();
}