#include "FileController.h"

FileController::FileController() {
}

//prints the content of the file given
void FileController::printFile(File& const file) {
	file.print();
}