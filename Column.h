#pragma once
#include <string>

class Column {
private:
	std::string columnName;
	//types the program will support are integer(also int), string & decimal
	std::string type;
	bool unique;

	std::string getColumnName() const;
	void setColumnName(std::string);
	std::string getType() const;
	void setType(std::string);
	bool getUnique() const;
	void setUnique(bool);

public:
	Column();
	Column(std::string, std::string, bool = false);
	
	//we only want these classes to have an access to the private members of the class
	friend class ColumnController;
	friend class Table;
};
