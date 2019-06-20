#include "Column.h"

Column::Column() :
	columnName(""), type("int"), unique(false) {
}

Column::Column(std::string name, std::string type, bool unique) :
	columnName(name), type(type), unique(unique) {
}

std::string Column::getColumnName() const {
	return this->columnName;
}

void Column::setColumnName(std::string name) {
	this->columnName = name;
}

std::string Column::getType() const {
	return this->type;
}

void Column::setType(std::string type) {
	this->type = type;
}

bool Column::getUnique() const {
	return this->unique;
}

void Column::setUnique(bool unique) {
	this->unique = unique;
}