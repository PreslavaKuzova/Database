#include "DatabaseController.h"
#include <algorithm>

DatabaseController::DatabaseController() {
}

//converts the name to lowercase
std::string DatabaseController::toLowercase(std::string name) {
	//here we use a library function to convert the name to lowercase
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return name;
}

//returns the name of the table from the fileName
std::string DatabaseController::getNameLoadedTable(std::string fileName) {
	std::vector<std::string> seglist = this->parseString(fileName, '/');
	fileName = seglist.back();
	return fileName.substr(0, fileName.find("."));
}

//parses a string
std::vector<std::string> DatabaseController::parseString(std::string str, char delimiter) {
	std::stringstream stream(str);
	std::string segment;
	std::vector<std::string> seglist;
	while (std::getline(stream, segment, delimiter)) {
		seglist.push_back(segment);
	}

	return seglist;
}

//load a file, create a table according to the columns in it and add it to the database given
void DatabaseController::load(Database& database, std::string fileName) {
	std::string tableName = this->getNameLoadedTable(fileName);

	if (this->tableExists(database, tableName)) {
		std::cout << "Table with name " << tableName << " has already been loaded.\n";
	}
	else {
		std::ifstream myfile(fileName);
		if (myfile.is_open()) {
			Table table(TableController().createTable(tableName));

			//discarding the first line of the file
			std::string line = "";
			std::getline(myfile, line);

			//getting the column names into a vector
			std::string columns = "";
			std::getline(myfile, columns);
			std::vector<std::string> columnList = this->parseString(columns, ' ');

			//getting the column types into a vector
			std::string types = "";
			std::getline(myfile, types);
			std::vector<std::string> typesList = this->parseString(types, ' ');

			//creating columns and adding them to the table
			for (int i = 0; i < typesList.size(); i++) {
				Column column = ColumnController().createColumn(columnList.at(i), typesList.at(i));
				TableController().addColumn(table, column);
			}

			File file(fileName);

			//adding the table and file to the database only after every check is done
			this->add(database, table, file);
		}
		else {
			std::cout << "Unable to open file from this directory. Please try again.\n";
		}
	}
}

//adds a new already created table to the database
void DatabaseController::add(Database& database, Table& const table, File& const file) {
	if (database.tableExists(TableController().getName(table))) {
		std::cout << "Error. There is already a table with name " << TableController().getName(table) << " in the database.\n";
	}
	else {
		database.addTable(table, file);
		std::cout << "Successfully added a new table to the database.\n";
	}
}

//creates an empty table and adds it to the database
void DatabaseController::create(Database& database, std::string tableName, File& const file) {
	if (database.tableExists(tableName)) {
		std::cout << "Error. There is already a table with name " << tableName << " in the database.\n";
	}
	else {
		Table table(TableController().createTable(tableName));
		database.addTable(table, file);
		std::cout << "Successfully added a new table to the database.\n";
	}
}

//removes a table from the database
void DatabaseController::remove(Database& database, std::string tableName) {
	if (database.empty()) {
		std::cout << "The database is empty, there is nothing to remove here.\n";
	}
	else {
		if (database.tableExists(tableName)) {
			database.removeTable(this->toLowercase(tableName));
			std::cout << "Successfully removed table " << tableName << std::endl;
		}
		else {
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
		}
		else {
			Table& table = this->returnTableByName(database, tableName);
			TableController().rename(table, newTableName);
		}
	}
	else {
		std::cout << "Error. There is no table with name " << tableName << ".\n";
	}
}

//prints the name of the tables in the database
void DatabaseController::showTables(Database& const database) {
	if (database.empty()) {
		std::cout << "Nothing to show here. The database is empty.\n";
	} else {
		std::cout << database.tableNames() << std::endl;
	}
}

//gives the information about the columns in the table (name and type)
void DatabaseController::describe(Database& const database, std::string tableName) {
	if (database.empty()) {
		std::cout << "Nothing to show here. The database is empty!" << std::endl;
	}
	else {
		if (database.tableExists(this->toLowercase(tableName))) {
			Table table = this->returnTableByName(database, tableName);
			TableController().tableInfo(table);
		}
		else {
			std::cout << "Sorry. There is no table " << tableName << " in the database.\n";
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

//returns the file related with the table with the given name
File& DatabaseController::returnFileByTableName(Database& const database, std::string tableName) {
	for (int i = 0; i <= database.getTop(); i++) {
		if (!toLowercase(tableName).compare(TableController().getName(database.tables[i]))) {
			return database.files[i];
		}
	}
}

//print the file related to the table with the given name
void DatabaseController::print(Database& const database, std::string tableName) {
	if (database.empty()) {
		std::cout << "Nothing to print. The database is empty!" << std::endl;
	}
	else {
		if (database.tableExists(this->toLowercase(tableName))) {
			FileController().printFile(this->returnFileByTableName(database, tableName));
		} else {
			std::cout << "Sorry. There is no table " << tableName << " in the database.\n";
		}
	}
}