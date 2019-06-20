#include "FileController.h"

FileController::FileController() {
}

//load a file, create a table according to the columns in it and add it to the database given
//TODO add the file to the Database
void FileController::load(Database& database, std::string file) {
	std::string tableName = this->getNameLoadedTable(file);
	
	if (DatabaseController().tableExists(database, tableName)) {
		std::cout << "Table with name " << tableName << " has already been loaded.\n";
	} else {
		std::ifstream myfile(file);
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

			//adding the table to the database only after every check is done
			DatabaseController().add(database, table);
		
		} else {
			std::cout << "Unable to open file from this directory. Please try again.\n";
		}
	}
}

//returns the name of the table from the fileName
std::string FileController::getNameLoadedTable(std::string fileName) {
	std::vector<std::string> seglist = this->parseString(fileName, '/');
	fileName = seglist.back();
	return fileName.substr(0, fileName.find("."));
}

std::vector<std::string> FileController::parseString(std::string str, char delimiter) {
	std::stringstream stream(str);
	std::string segment;
	std::vector<std::string> seglist;
	while (std::getline(stream, segment, delimiter)) {
		seglist.push_back(segment);
	}

	return seglist;
}