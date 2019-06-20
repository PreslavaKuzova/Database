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
	FileController().load(database, "C:/Users/presl/Desktop/table1.txt");
	DatabaseController().showTables(database);
	return 0;
}