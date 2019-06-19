#include "Database.h"
#include "Table.h"
#include "DatabaseController.h"
#include "TableController.h"
#include <algorithm>

DatabaseController::DatabaseController() {
}

//converts the name to lowercase
std::string DatabaseController::toLowercase(std::string name) {
	//here we use a library function to convert the name to lowercase
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return name;
}

//adds a new already created table to the database
void DatabaseController::add(Database& database, Table& const table) {
	if (database.tableExists(TableController().getName(table))) {
		std::cout << "Error. There is already a table with name " << TableController().getName(table) << " in the database.\n";
	} else {
		database.addTable(table);
		std::cout << "Successfully added a new table to the database.\n";
	}
}

//creates an empty table and adds it to the database
void DatabaseController::create(Database& database, std::string tableName) {
	if (database.tableExists(tableName)) {
		std::cout << "Error. There is already a table with name " << tableName << " in the database.\n";
	} else {
		Table table(TableController().createTable(tableName));
		database.addTable(table);
		std::cout << "Successfully added a new table to the database.\n";
	}
}

//removes a table from the database
void DatabaseController::remove(Database& database, std::string tableName) {
	if (database.empty()) {
		std::cout << "The database is empty, there is nothing to remove here.\n";
	} else {
		if (database.tableExists(tableName)) {
			database.removeTable(this->toLowercase(tableName));
			std::cout << "Successfully removed table " << tableName << std::endl;
		} else {
			std::cout << "There is no table with name " << tableName << " in the database.\n";
		}
	}
}

//checks whether a table with such name exists
bool DatabaseController::tableExists(Database& database, std::string tableName) {
	return database.tableExists(this->toLowercase(tableName));
}

//renames a table if such exists
void DatabaseController::renameTable(Database& database, std::string tableName, std::string newTableName) {
	tableName = this->toLowercase(tableName);
	newTableName = this->toLowercase(newTableName);
	if (database.tableExists(tableName)) {
		if (database.tableExists(newTableName)) {
			std::cout << "Error. There is already a table with name " << newTableName << 
				" in the database.\n";
		} else {
			Table& table = this->returnTableByName(database, tableName);
			TableController().rename(table, newTableName);
		}
	} else {
		std::cout << "Error. There is no table with name " << tableName << ".\n";
	}	
}

//prints the name of the tables in the database
void DatabaseController::showTables(Database& const database) {
	std::cout << database.tableNames();
}

//gives the information about the columns in the table (name and type)
void DatabaseController::describe(Database& const database, std::string tableName) {
	if (database.empty()) {
		std::cout << "Nothing to show here. The database is empty!" << std::endl;
	} else {
		if (database.tableExists(this->toLowercase(tableName))) {
			Table table = this->returnTableByName(database, tableName);
			TableController().tableInfo(table);
		} else {
			std::cout << "sorry. There is no table " << tableName << " in the database.\n";
		}
	}
}

//returns a table by it's name
//it is only being used after having the checks done in another method
Table& DatabaseController::returnTableByName(Database& const database, std::string tableName) {
	for (int i = 0; i <= database.getTop(); i++) {
		if (!toLowercase(tableName).compare(TableController().getName(database.tables[i]))) {
			return database.tables[i];
		}
	}
}