#pragma once

#ifndef FILE_CONTROLLER_HEADER
#define FILE_CONTROLLER_HEADER

#include "File.h"

class FileController {
private:
public:
	FileController();
	void printFile(File& const);
	void selectFromFile(File& const, int, std::string);
	void insertColumn(File&);

	//to be continued
	void updateFile();
	void deleteRow();
	void insertRow();
	
	void innerJoin();
	void count();
	void aggregate();
};
#endif
