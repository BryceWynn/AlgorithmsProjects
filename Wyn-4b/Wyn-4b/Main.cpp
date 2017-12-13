// Wyn-4a sudoku creater
// runs Board header file to read in and create the sudoku puzzles
//currently cannot solve sudokus
//
// updated to solve and output solved sudokus
//will output number of recursions for each puzzle as well as average number of recursions at end
// BW 31OCT16

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
	if (!fin) // if file does not open
	{
		cerr << "Cannot open " << fileName << endl;
		getchar();
		exit(1);
	}
	vector<Board> boardVector; // intitalize vector of boards
	int incrementer = 0; // used to increment btw boards
	try
	{
		long totalRecursions = 0; // initialize recursions counter to  0
		int recursions; // term for the recursions for each board
		int puzzles = 0; // puzzles solved
		bool invalidSudoku = false; // term used for bad input
		while (fin && fin.peek() != 'Z') // while not at eof
		{
			puzzles++; // puzzle count ++
			boardVector.push_back(Board(SQUARESIZE)); // make a new board class for new board
			boardVector[incrementer].initialize(fin); // intiialize board with next row of harecters
			boardVector[incrementer].print(); // print unsolved  booard
			invalidSudoku = boardVector[incrementer].startConflicts(); // check to see if board is solvablle + print conflicts
			if (invalidSudoku == true) { // error term if bad board
				cout << "unsolvable sudoku, skipping and proceeding to next value" << endl;
				invalidSudoku = false;
			}
			//boardVector[incrementer].printConflicts();   conflicts not printed in this version for readability
			else {
				boardVector[incrementer].puzzleSolver(); // solve puzzle
				boardVector[incrementer].print(); // print solved puzzle
				recursions = boardVector[incrementer].returnRecursions(); // return recursions to solve the puzzle
				cout << "function recursed " << recursions << "times" << endl; // print recursions it took to solve the puzzle
				totalRecursions += recursions; // add recursions to total recursions
				incrementer++; // increments incrementer
			}
		}
		// prints out average recursions.
		cout << " software sovled " << puzzles << " sudokus, averaging " << totalRecursions / puzzles << "recursions per puzzle"
			<< endl << endl;
		getchar();
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	getchar();
}



