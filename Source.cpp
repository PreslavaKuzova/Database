#include <iostream>
#include "Column.h"
#include "Table.h"
#include "Database.h"
#include "ColumnController.h"
#include "TableController.h"
#include "DatabaseController.h"

int main() {
	//have to use the copy constructor
	Column column(ColumnController().createColumn("name", "incorrect type"));
	std::cout << ColumnController().getColumnInfo(column);

	Table table(TableController().createTable("!awesome table!"));
	TableController().describe(table);
	TableController().createColumn(table, "new column", "INT");
	TableController().describe(table);
	TableController().columns(table);
	TableController().addColumn(table, column);
	TableController().columns(table);
	TableController().describe(table);

	Database database("new database");
	DatabaseController().create(database, "table1");
	DatabaseController().create(database, "table2");
	DatabaseController().create(database, "table3");
	DatabaseController().tableNames(database);
	std::cout << std::endl << "Table exists: " << DatabaseController().tableExists(database, "tale1");
	std::cout << "\nRename: "<< std::endl;
	DatabaseController().renameTable(database, "table1", "AWESOME TABLE");
	DatabaseController().tableNames(database);
	DatabaseController().remove(database, "table2");
	DatabaseController().tableNames(database);
	DatabaseController().create(database, "table3");
	return 0;
}