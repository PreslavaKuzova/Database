#include <iostream>
#include "Column.h"
#include "Table.h"
#include "Database.h"
#include "ColumnController.h"
#include "TableController.h"
#include "DatabaseController.h"

int main() {
	Database database("new database");
	DatabaseController().create(database, "table1");
	DatabaseController().create(database, "table2");
	DatabaseController().create(database, "table3");
	DatabaseController().showTables(database);
	DatabaseController().renameTable(database, "table1", "newname");
	DatabaseController().showTables(database);
	DatabaseController().describe(database, "TAble3");

	DatabaseController().renameTable(database, "TablE3", "tabLe3new");

	DatabaseController().showTables(database);
	
	return 0;
}