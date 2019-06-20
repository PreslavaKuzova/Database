#include "File.h"

File::File() {
	this->rows = 0;
	this->columns = 0;
	this->array = new std::string *[this->rows];
	array[0] = new std::string[this->columns];
}

//TODO look again here - some changes will apply
File::File(std::string fileName) {
	std::ifstream myfile(fileName);

	std::string dimensions = "";
	std::getline(myfile, dimensions);
	
	this->findDimensions(dimensions);

	//creating the two dimentional array
	this->array = new std::string*[this->rows];
	for (int i = 0; i < this->rows; i++) {
		this->array[i] = new std::string[this->columns];
	}

	//we discard two lines of code - the ones that include the information of the columns
	std::string line = "";
	for (int i = 0; i < 2; i++) {
		std::getline(myfile, line);
	}

	//storing the data of the file into the array
	if (myfile.is_open()) {
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) {
				myfile >> this->array[i][j];
			}
		}
	}
}

File::File(const File& file): rows(file.rows), columns(file.columns) {
	this->array = new std::string*[this->rows];
	for (int i = 0; i < this->rows; i++) {
		this->array[i] = new std::string[this->columns];
	}

	//transfer the data from the file.array to array
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			this->array[i][j] = file.array[i][j];
		}
	}
}

File& File::operator=(const File& file) {
	if (this != &file) {
		this->rows = file.rows;
		this->columns = file.columns;

		//deleting the array
		for (int i = 0; i < this->rows; i++) {
			delete[] this->array[i];
		}
		delete[] this->array;

		//creating a new array
		this->array = new std::string*[this->rows];
		for (int i = 0; i < this->rows; i++) {
			this->array[i] = new std::string[this->columns];
		}

		//transfer the data from the file.array to array
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) {
				this->array[i][j] = file.array[i][j];
			}
		}
	}
	return *this;
}

File::~File() {
	for (int i = 0; i < this->rows; i++) {
		delete[] this->array[i];
	}
	delete[] this->array;
}

//assigning the values of the dimensions of the array
void File::findDimensions(std::string stringDimensions) {
	//here we use library functions to get the the dimensions and separate them
	std::stringstream dimensions(stringDimensions);
	std::string segment;
	std::vector<std::string> seglist;
	
	while (std::getline(dimensions, segment, ' ')) {
		seglist.push_back(segment);
	}

	//here we use a library function to convert the values from string to int
	this->columns = std::stoi(seglist.at(0));
	this->rows = std::stoi(seglist.at(1));
}

//printing the file
void File::print() {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			std::cout << array[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//returns the number of columns
int File::getColumns() const {
	return this->columns;
}

//returns the number of rows
int File::getRows() const {
	return this->rows;
}