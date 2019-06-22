#pragma once

#ifndef FILE_HEADER
#define FILE_HEADER

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

class File {
private:
	int columns;
	int rows;
	std::string **array;

	void findDimensions(std::string);
	bool isEmpty();

	void print();
	int getColumns() const;
	int getRows() const;

	void addNewColumn();
	void addNewRow(std::string[]);
	int countRows(int, std::string);
	void deleteRows(int, std::string);

public:
	File();
	File(std::string);
	File(const File&);
	File& operator=(const File&);
	~File();

	friend class FileController;
	friend class Database;
};

#endif