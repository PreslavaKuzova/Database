#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "ColumnController.h"
#include "TableController.h"
#include "DatabaseController.h"
#include "Database.h"
#include "File.h"

class FileController {
private:
	std::string getNameLoadedTable(std::string);
	std::vector<std::string> parseString(std::string, char);
public:
	FileController();
	
	void load(Database&, std::string);
	
	void save();
	void select();
	void update();
	void deleteRow();
	void insert();
	void innerJoin();
	void count();
	void aggregate();
};