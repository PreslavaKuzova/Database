#include "Database.h"
#include "Table.h"
#include "DatabaseController.h"
#include "TableController.h"
#include <algorithm>

DatabaseController::DatabaseController() {
}

//converts the name to lowercase
std::string DatabaseController::verifyDatabaseName(std::string name) {
	//here we use a library function to convert the name to lowercase
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return name;
}

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
			database.removeTable(tableName);
			std::cout << "Successfully removed table " << tableName << std::endl;
		} else {
			std::cout << "There is no table with name " << tableName << " in the database.\n";
		}
	}
}

//checks whether a table with such name exists
bool DatabaseController::tableExists(Database& database, std::string tableName) {
	return database.tableExists(tableName);
}

//renames a table if such exists
void DatabaseController::renameTable(Database& database, std::string tableName, std::string newTableName) {
	if (database.tableExists(tableName)) {
		if (database.tableExists(newTableName)) {
			std::cout << "Error. There is already a table with name " << newTableName << 
				" in the database.\n";
		} else {
			for (int i = 0; i <= database.getTop(); i++) {
				if (!tableName.compare(TableController().getName(database.tables[i]))) {
					TableController().rename(database.tables[i], newTableName);
				}
			}
		}
	} else {
		std::cout << "Error. There is no table with name " << tableName << ".\n";
	}	
}

//prints the name of the tables in the database
void DatabaseController::tableNames(Database& const database) {
	std::cout << database.tableNames();
}