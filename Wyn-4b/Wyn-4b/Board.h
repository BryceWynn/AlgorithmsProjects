#pragma once
// header file for board class for sudoku solver
// contains private matrix member for the sudoku
//contains three seperate vectors of vectors of bools for truth table
// for every row, column, and square there is a truth table stating which values are already present in them
// contains functions to initalize and print the sudokus and truth tables
// currently cannot solve the sudokus
// BW 22OCT16
//
// update to be able to solve sudokus and count recursions
// BW 31OCT16

#pragma once
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"

class Board
	// Stores the entire Sudoku board
{
public:
	Board(int boardSize); // initializer, sets sudoku size
	void initialize(ifstream &fin); // sets starting values for sudoku
	void print(); // prints out sudoku
	bool startConflicts(); // initializes the conflict tables with the starting values
	void printConflicts(); // prints out conflict tables
	int squareTruthSelect(int& row, int& column); // function used for determining which square table to do logic with
	bool validCheck(int& row, int& column, int& value); // returns true if number can be added there
	void truthUpdater(int&row, int&column, int& value); // updates truth table
	bool isSolved(); // returns true if solved
	bool puzzleSolver(); // solves sudoku
	int digitToSolve(); // selects which digit in the sudoku to solve for
	int returnRecursions(); // gives number of recursions needed to solve
	
	// below functions included due to template but not utilized in fuction
	bool isBlank(int, int); // states if a square is zero, not used but included due to template
	int getCell(int, int); // returns value in a cell , not used but includede due to template
	void setCell(int i, int j, int val); //  sets a cell calue, not used but included due to template

private:
	// The following matrices go from 1 to boardSize in each
	// dimension. I.e. they are each (boardSize+1) X (boardSize+1)
	matrix<int> boardMatrix; // sudoku matrix
	vector <vector <bool> > rowTruthTables; // truth vectors for rows
	vector <vector <bool> > columnTruthTables; // truth vectors for columns
	vector <vector <bool> > squareTruthTables; // truth vectors for squares
	vector <bool> digitPossibilities; // used in solver logic, defined early to save reinitializing vector
	int size; // used so often in functions that defining here saves time
	int squareSize; // dimensions of smaller square, used to prevent need of calculating sqrt
	long recursions = 0; // number of times that the puzzle recurses to solve
};


