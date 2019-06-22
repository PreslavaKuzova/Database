#include <iostream>
#include <string>
#include "Column.h"
#include "Table.h"
#include "Database.h"
#include "ColumnController.h"
#include "TableController.h"
#include "DatabaseController.h"
#include "FileController.h"
#include "File.h"

void printMenu();

int main() {
	Database database("unknown");
	
	int answear = 13;
	std::string table = "";
	std::string newName = "";
	std::string columnType = "";
	std::string location = "";
	std::string columnName = "";

	while (answear != 0) {
		switch (answear) {
		case 1:
			std::cout << "Please enter the location you want to get the file from: ";
			std::cin >> location;
			DatabaseController().load(database, location);
			break;
		case 2:
			DatabaseController().showTables(database);
			break;
		case 3:
			std::cout << "Please choose a table which you want to get the information of: ";
			std::cin >> table;
			DatabaseController().describe(database, table);
			break;
		case 4:
			std::cout << "Please choose a table you want to rename: ";
			std::cin >> table;
			std::cout << "Please choose a new name: ";
			std::cin >> newName;
			DatabaseController().renameTable(database, table, newName);
			break;
		case 5:
			std::cout << "Please choose a table you want to save: ";
			std::cin >> table;
			std::cout << "Please choose location you want to save it in: ";
			std::cin >> location;
			DatabaseController().save(database, table, location);
			break;
		case 6:
			std::cout << "Please choose a table you select from: ";
			std::cin >> table;
			DatabaseController().select(database, table);
			break;
		case 7:
			std::cout << "Please choose a table you want to add a column to: ";
			std::cin >> table;
			std::cout << "Please choose a name for the column: ";
			std::cin >> newName;
			std::cout << "Please choose column type: ";
			std::cin >> columnType;
			DatabaseController().addColumn(database, table, newName, columnType);
			break;
		case 8:
			std::cout << "Please choose a table you want to update: ";
			std::cin >> table;
			DatabaseController().update(database, table);
			break;
		case 9:
			std::cout << "Please choose a table you want to add a new row to: ";
			std::cin >> table;
			DatabaseController().insertRow(database, table);
			break;
		case 10:
			std::cout << "Please choose a table you want to delete rows from: ";
			std::cin >> table;
			DatabaseController().deleteRows(database, table);
			break;
		case 11:
			std::cout << "Please choose a table you want to get a count of results: ";
			std::cin >> table;
			std::cout << "Result: " << DatabaseController().count(database, table) << std::endl;
			break;
		case 12:
			std::cout << "Please choose a table you want to print: ";
			std::cin >> table;
			DatabaseController().print(database, table);
			break;
		case 13:
			printMenu();
			break;
		case 0:
			return 0;
		default:
			std::cout << "Invalid command chosen. Please try again with another option.\n";
			break;
		}
		std::cout << std::endl;
		std::cout << "Please choose an option from the given menu: ";
		std::cin >> answear;
	}
}

void printMenu() {
	std::cout << "1. Load a table." << std::endl;
	std::cout << "2. Show names of all loaded tables." << std::endl;
	std::cout << "3. Give infomation about a loaded table." << std::endl;
	std::cout << "4. Rename a table." << std::endl;
	std::cout << "5. Save a table in a file." << std::endl;
	std::cout << "6. Select from table." << std::endl;
	std::cout << "7. Add new column to a table." << std::endl;
	std::cout << "8. Update a table." << std::endl;
	std::cout << "9. Insert a row in a table." << std::endl;
	std::cout << "10. Delete rows from a table." << std::endl;
	std::cout << "11. Count the rows that contain particular value. " << std::endl;
	std::cout << "12. Print a table." << std::endl;
	std::cout << "13. Print the menu again." << std::endl;
	std::cout << "0. To exit the program." << std::endl;
}