// header file for board class for sudoku solver
// contains private matrix member for the sudoku
//contains three seperate vectors of vectors of bools for truth table
// for every row, column, and square there is a truth table stating which values are already present in them
// contains functions to initalize and print the sudokus and truth tables
// currently cannot solve the sudokus
// BW 22OCT16

#pragma once
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"

class Board
	// Stores the entire Sudoku board
{
public:
	Board(int boardSize); // initializer, sets sudoku size
	//void clear(); 
	void initialize(ifstream &fin); // sets starting values for sudoku
	void print(); // prints out sudoku
	bool isBlank(int, int); 
	int getCell(int, int); 
	void setCell(int i, int j, int val); 
	void startConflicts(); // initializes the conflict tables with the starting values
	void printConflicts(); // prints out conflict tables
	int squareTruthSelect(int& row, int& column); // function used for determining which square table to do logic with
	bool validCheck(int& row, int& column, int& value);
	void truthUpdater(int&row, int&column, int& value);
	bool isSolved();

private:
	// The following matrices go from 1 to boardSize in each
	// dimension. I.e. they are each (boardSize+1) X (boardSize+1)
	matrix<int> boardMatrix; // sudoku matrix
	vector <vector <bool> > rowTruthTables; // truth vectors for rows
	vector <vector <bool> > columnTruthTables; // truth vectors for columns
	vector <vector <bool> > squareTruthTables; // truth vectors for squares
	int size; // used so often in functions that defining here saves time
	int squareSize; // dimensions of smaller square, used to prevent need of calculating sqrt
	vector <vector <bool> > rowTestedTables; // tested tables for rows
	// this is initialized identically to the row truth tables
	//afterwards only tracks the tested square values
};