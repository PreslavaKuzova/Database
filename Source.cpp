#include <iostream>
#include "Column.h"
#include "Table.h"
#include "Database.h"
#include "ColumnController.h"
#include "TableController.h"
#include "DatabaseController.h"
#include "FileController.h"
#include "File.h"

int main() {
	Database database("new database");
	DatabaseController().load(database, "C:/Users/presl/Desktop/table1.txt");
	DatabaseController().load(database, "C:/Users/presl/Desktop/table1.txt");
	DatabaseController().showTables(database);
	DatabaseController().describe(database, "table1");
	DatabaseController().print(database, "table1");
	//we have to make sure the value entered matches the data type of the column
	DatabaseController().select(database, "table1", 2, "6.00");
	DatabaseController().addColumn(database, "table1", "column4", "int");
	DatabaseController().print(database, "table1");
	std::cout << DatabaseController().count(database, "table1", 2, "6.00") << std::endl;
	//we have to make sure the value entered matches the data type of the column
	DatabaseController().update(database, "table1", 2, "6.00", 3, "7.00");
	DatabaseController().print(database, "table1");
	DatabaseController().remove(database, "table1");
	DatabaseController().remove(database, "table1");
	DatabaseController().showTables(database);
	return 0;
}