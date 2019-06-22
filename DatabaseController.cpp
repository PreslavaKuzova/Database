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

//allows to enter integers only
int DatabaseController::inputInt() {
	int value = 0;
	std::cin >> value;
	while (std::cin.fail()) {
		std::cout << "Invalid input! Please enter integers only!" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> value;
	}
	return value;
}

//allows to enter only decimals only
float DatabaseController::inputDecimal() {
	float value = 0.0;
	std::cin >> value;

	while (std::cin.fail() || (std::cin.peek() != '\r' && std::cin.peek() != '\n')) {
		std::cout << "Invalid Input! Please input a numerical value!" << std::endl;
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cin >> value;
	}

	return value;
}

//allows us to enter a string
std::string DatabaseController::inputString() {
	std::string str = "";
	std::cin >> str;
	return str;
}

//makes sure the input is correct depending on the column type
std::string DatabaseController::inputDependingOnType(std::string type) {
	if (!type.compare("int")) {
		int value = this->inputInt();
		return std::to_string(value);
	} else if (!type.compare("decimal")) {
		float value = this->inputDecimal();
		return std::to_string(value).substr(0, 4);
	}
	std::string value = this->inputString();
	return value;
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
	} else {
		if (database.tableExists(this->toLowercase(tableName))) {
			FileController().printFile(this->returnFileByTableName(database, tableName));
		} else {
			std::cout << "Sorry. There is no table " << tableName << " in the database.\n";
		}
	}
}

//prints the rows that contain <value> in the given column number of the given table
void DatabaseController::select(Database& const database, std::string tableName) {
	if (database.empty()) {
		std::cout << "Nothing to print. The database is empty!" << std::endl;
	} else {
		if (database.tableExists(this->toLowercase(tableName))) {
			Table& table = this->returnTableByName(database, tableName);
			
			std::cout << "Enter search column index: ";
			int searchColumnNumber = this->inputInt();

			if (TableController().columnExistsByIndex(table, searchColumnNumber)) {
				File file = this->returnFileByTableName(database, tableName);

				std::string typeSearch = TableController().getColumnTypeFromIndex(table, searchColumnNumber);
				std::cout << "Enter search column value: ";
				std::string searchValue = this->inputDependingOnType(typeSearch);

				FileController().selectFromFile(file, searchColumnNumber, searchValue);
			} else {
				std::cout << "Invalid column identificator. Please try again with a correct column.\n";
			}
		} else {
			std::cout << "Sorry. There is no table " << tableName << " in the database.\n";
		}
	}
}

//adds new column to the file, related to the table with tableName and assigns the new values to NULL
void DatabaseController::addColumn(Database& const database, std::string tableName, std::string columnName, std::string columnType) {
	if (database.tableExists(this->toLowercase(tableName))) {
		Table& table = this->returnTableByName(database, tableName);
		if (TableController().columnExists(table, this->toLowercase(columnName))) {
			std::cout << "There is already a column " << columnName << 
				" in table " << tableName << std::endl;
		} else {
			TableController().createColumn(table, columnName, columnType);
			File& file = this->returnFileByTableName(database, tableName);
			FileController().insertColumn(file);
		}
	} else {
		std::cout << "Sorry. There is no table " << tableName << " in the database.\n";
	}
}

//returns the number of rows in table tableName that contain value in column columnNumber
int DatabaseController::count(Database& const database, std::string tableName) {
	if (database.empty()) {
		std::cout << "No results found. The database is empty." << std::endl;
		return 0;
	} else {
		if (database.tableExists(this->toLowercase(tableName))) {
			Table& table = this->returnTableByName(database, tableName);
			
			std::cout << "Enter search column index: ";
			int searchColumnNumber = this->inputInt();
			
			if (TableController().columnExistsByIndex(table, searchColumnNumber)) {
			
				File& file = this->returnFileByTableName(database, tableName);
	
				std::cout << "Enter search column value: ";
				std::string value = this->inputString();
				
				return FileController().countRows(file, searchColumnNumber, value);
			
			} else {
				std::cout << "Invalid column identificators. Please try again with correct columns.\n";
			}
		} else {
			std::cout << "Sorry. There is no table " << tableName << " in the database.\n";
			return 0;
		}
	}
}

//for every row of the given file where the column searchColumnNumber contains value
//modifies column targetColumnNumber to contain targetValue
void DatabaseController::update(Database& database, std::string tableName) {
	if (database.empty()) {
		std::cout << "Nothing to modify. The database is empty!" << std::endl;
	} else {
		if (database.tableExists(this->toLowercase(tableName))) {
			
			Table& table = this->returnTableByName(database, tableName);
			
			std::cout << "Enter search column index: ";
			int searchColumnNumber = this->inputInt();
			std::cout << "Enter target column index: ";
			int targetColumnNumber = this->inputInt();

			if (TableController().columnExistsByIndex(table, searchColumnNumber) &&
				TableController().columnExistsByIndex(table, targetColumnNumber)) {
				
				std::string typeSearch = TableController().getColumnTypeFromIndex(table, searchColumnNumber);
				std::string typeTarget = TableController().getColumnTypeFromIndex(table, targetColumnNumber);

				std::cout << "Enter search column value: ";
				std::string searchValue = this->inputDependingOnType(typeSearch);
				std::cout << "Enter search target column update value: ";
				std::string targetValue = this->inputDependingOnType(typeTarget);

				File& file = this->returnFileByTableName(database, tableName);
				FileController().updateFile(file, searchColumnNumber, searchValue, targetColumnNumber, targetValue);
			} else {
				std::cout << "Invalid column identificators. Please try again with correct columns.\n";
			}
		} else {
			std::cout << "Sorry. There is no table " << tableName << " in the database.\n";
		}
	}
}

//saves the table into a .txt file
void DatabaseController::save(Database& const database, std::string tableName, std::string location) {

}