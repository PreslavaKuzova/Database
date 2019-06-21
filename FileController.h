#pragma once

#ifndef FILE_CONTROLLER_HEADER
#define FILE_CONTROLLER_HEADER

#include "File.h"

class FileController {
private:
	FileController();
	void printFile(File& const);
	void selectFromFile(File& const, int, std::string);
	void insertColumn(File&);
	int countRows(File& const, int, std::string);
	void updateFile(File&, int, std::string, int, std::string);
public:
	//to be continued
	void deleteRow();
	void insertRow();
	void innerJoin();
	void aggregate();

	friend class DatabaseController;
};
#endif
