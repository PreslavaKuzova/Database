#include "ColumnController.h"
#include <algorithm> 

ColumnController::ColumnController() {
}

//creates a column with a given name
Column ColumnController::createColumn(std::string name, std::string type, bool unique) {
	Column column(this->verifyColumnName(name), this->verifyColumnType(type), unique);
	return column;
}

//converts the name to lowercase
std::string ColumnController::verifyColumnName(std::string name) {
	//here we use a library function to convert the name to lowercase
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return name;
}

//checks whether the type is correct, if it is not - returns "string"
std::string ColumnController::verifyColumnType(std::string type) {
	//here we use a library function to convert the type to lowercase
	//this is done to prevent any further malfunction
	std::transform(type.begin(), type.end(), type.begin(), ::tolower);

	if (!type.compare("int") || !type.compare("integer")) {
		return "int";
	}
	else if (!type.compare("decimal")) {
		return "decimal";
	}

	return "string";
}

//returns a string containing the name and the type of the column
std::string ColumnController::getColumnInfo(Column& column) {
	return "Name: " + column.getColumnName() + ", type: " + column.getType() + "\n";
}

//returns the column name
std::string ColumnController::getColumnName(Column& const column) {
	return column.getColumnName();
}

