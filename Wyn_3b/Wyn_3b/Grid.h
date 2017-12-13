/*Header File for Grid
* reads in a grid of numbers to create a matrix
* contains functions to return matrix dimensions
* also includes return function for a given matrix value
* BW 08OCT16
*/

#pragma once
#include "WordList.h" // included due to mutual header files needed.
#include "d_matrix.h"
using namespace std;

class Grid {
public:
	void fileReader(string filename);// reads in files
	int rowReturner(); // returns number of row 
	int columnReturner(); // returns number of columns
	char charReturner(int x, int y); // returns the charecter at a given position


private:
	matrix<char> charMat;

};