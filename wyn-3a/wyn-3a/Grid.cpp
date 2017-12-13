/* Source file for Grid header
* contains all functions defined in Grid.h
* each function contains description before lead of identifier
* BW 08OCT16
*/
#include "Grid.h"
#include <fstream>

// reads in grid
void Grid::fileReader(string fileName) {
	ifstream gridIn;
	gridIn.open(fileName.c_str()); // opens gridfile
	if (!gridIn) throw rangeError("grid filename not present"); // ensures gridfile was there to open
	int matSizeReader;
	char fileRead = '\n';
	int x = 0;
	int row = 0;
	int column = 0;
	gridIn >> matSizeReader;// knowing it is an nxn matrix, first number not needed so input immediatly taken
	gridIn >> matSizeReader; // this input is used to set dimension
	gridIn.get(fileRead); // clears first /n
	charMat.resize(matSizeReader, matSizeReader); // set amtrix dimensions
	while (!gridIn.eof()) { // while file sint closed
		gridIn.get(fileRead); // take next char
		if (fileRead != '\n' && fileRead != ' ') { // ensures /n increments row and spaces are ignored
			charMat[row][column] = fileRead; // otherwise set next matrix value
			column++;
		}
		if (fileRead == '\n') { // if new line, increment matrix value
			column = 0;
			row++;
		}
	}
	return;
}

//returns rows in matrix
int Grid::rowReturner() {
	return (charMat.rows());
}

// returns columns in matrix
int Grid::columnReturner() {
	return (charMat.cols());
}

// returns chars in matrix
char Grid::charReturner(int x, int y) {
	return (charMat[x][y]);
}


