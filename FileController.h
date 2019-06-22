#pragma once

#ifndef FILE_CONTROLLER_HEADER
#define FILE_CONTROLLER_HEADER

#include "File.h"

class FileController {
private:
	FileController();
	int getRows(File& const);
	int getColumns(File& const);
	std::string returnRowStringByIndex(File& const, int);
	void printFile(File& const);
	void selectFromFile(File& const, int, std::string);
	void insertColumn(File&);
	int countRows(File& const, int, std::string);
	void updateFile(File&, int, std::string, int, std::string);
	void insertRow(File&, std::string[]);
	void deleteRows(File&, int, std::string);
public:
	void innerJoin();
	void aggregate();

	friend class DatabaseController;
};
#endif
