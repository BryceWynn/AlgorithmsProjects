// Wyn-4a sudoku creater
// runs Board header file to read in and create the sudoku puzzles
//currently cannot solve sudokus


#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include "d_except.h"

#define SQUARESIZE 3 //sets size of sudoku boards used

int main()
{
	ifstream fin;

	// Read the sample grid from the file.
	string fileName = "sudoku.txt";
	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		getchar();
		exit(1);
	}
	vector<Board> boardVector;
	int incrementer = 0;
	try
	{
		while (fin && fin.peek() != 'Z')
		{
			boardVector.push_back(Board(SQUARESIZE));
			boardVector[incrementer].initialize(fin);
			boardVector[incrementer].print();
			boardVector[incrementer].startConflicts();
			boardVector[incrementer].printConflicts();
			incrementer++;
			cout << "please press enter to get next sudoku" << endl;
			getchar();
		}
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	getchar();
}



