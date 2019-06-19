#include <iostream>
#include "Column.h"
#include "Table.h"
#include "Database.h"
#include "ColumnController.h"
#include "TableController.h"

int main() {
	//have to use the copy constructor
	Column column(ColumnController().createColumn("name", "incorrect type", true));
	std::cout << ColumnController().getColumnInfo(column);

	Table table(TableController().createTable("!awesome table!"));
	TableController().describe(table);
	TableController().addColumn(table, "new column", "INT");
	TableController().describe(table);
	TableController().columns(table);

	return 0;
}