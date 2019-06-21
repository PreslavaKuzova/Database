#include "FileController.h"

FileController::FileController() {
}

//prints the content of the file given
void FileController::printFile(File& const file) {
	if (file.isEmpty()) {
		std::cout << "The file is empty. Nothing to print.\n";
	} else {
		file.print();
	}
}

//prints from the file the rows in which the there is the given value in column columnNumber
void FileController::selectFromFile(File& const file, int columnNumber, std::string value) {
	if (file.isEmpty()) {
		std::cout << "The file is empty. Nothing to print.\n";
	} else {
		std::cout << "Result:\n";
		for (int i = 0; i < file.getRows(); i++) {
			if (!value.compare(file.array[i][columnNumber])) {
				for (int j = 0; j < file.getColumns(); j++) {
					std::cout << file.array[i][j] + " ";
				}
				std::cout << std::endl;
			}
		}
	}
}

//inserts a new column to the file and assigns NULL to the cells
void FileController::insertColumn(File& file) {
	if (file.isEmpty()) {
		std::cout << "The provided file is empty. Creating a new column.\n";
	}
	file.addNewColumn();
}

//returns the number of rows that contain the value in column columnNumber
int FileController::countRows(File& const file, int columnNumber, std::string value){
	int count = 0;
	if (file.isEmpty()) {
		std::cout << "The file is empty. No results.\n";
		return 0;
	} else {
		
		for (int i = 0; i < file.getRows(); i++) {
			if (!value.compare(file.array[i][columnNumber])) {
				count++;
			}
		}
	}

	return count;
}

void FileController::updateFile(File& file, int searchColumn, std::string value, int targetColumn, std::string target) {
	if (file.isEmpty()) {
		std::cout << "The file is empty. Nothing to print.\n";
	} else {
		for (int i = 0; i < file.getRows(); i++) {
			if (!value.compare(file.array[i][searchColumn])) {
				file.array[i][targetColumn] = target;
			}
		}
	}
}