#pragma once

#ifndef FILE_CONTROLLER_HEADER
#define FILE_CONTROLLER_HEADER

#include "File.h"

class FileController {
private:
public:
	FileController();
	void printFile(File& const);
	
	//to be continued
	void select();
	void updateFile();
	void deleteRow();
	void insertRow();
	void innerJoin();
	void count();
	void aggregate();
};
#endif
