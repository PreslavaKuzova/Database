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
	DatabaseController().select(database, "table1", 2, "6.00");
	DatabaseController().addColumn(database, "table1", "column4", "int");
	DatabaseController().describe(database, "table1");
	DatabaseController().print(database, "table1");
	return 0;
}