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
	DatabaseController().load(database, "C:/Users/presl/Desktop/table2.txt");
	//DatabaseController().print(database, "table1");
	//DatabaseController().print(database, "table2");
	//DatabaseController().select(database, "table1");
	//DatabaseController().addColumn(database, "table1", "column4", "int");
	//DatabaseController().print(database, "table1");
	//std::cout << DatabaseController().count(database, "table1") << std::endl;
	//DatabaseController().update(database, "table1");
	//DatabaseController().insertRow(database, "table1");
	DatabaseController().print(database, "table1");
	DatabaseController().deleteRows(database, "table1");
	DatabaseController().print(database, "table1");
	return 0;
}