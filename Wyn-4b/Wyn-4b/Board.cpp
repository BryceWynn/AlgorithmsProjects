// cpp file for board header 
// contains definitions for all Board class files
// BW 22OCT16
//
// File updated to solve sudokus
//uses recursively called puzzlesolved, as well as digitToSolve to complete sudokus
//function also added to return the recursions needed to solve the puzzle
// BW 31OCT16

#include "Board.h"

// board initializer
// takes in an int to set sudoku puzzle size than sets up remaining variables accordingly
Board::Board(int boardSize) {
	size = boardSize*boardSize;
	squareSize = boardSize; // stored to prevent squareRoot operations later due to their being processor intensive
	boardMatrix.resize(size, size); //sets matrix dimensions
	rowTruthTables.resize(size); // sets row vector dimensions
	for (int i = 0; i < size; i++) rowTruthTables[i].resize(size); // sets each row vectors dimension
	columnTruthTables.resize(size);// sets column vector dimesnions
	for (int i = 0; i < size; i++) columnTruthTables[i].resize(size);//sets each column vectors dimensions
	squareTruthTables.resize(size);// sets square vector dimensions
	for (int i = 0; i < size; i++) squareTruthTables[i].resize(size); //sets each square columns dimensions
	digitPossibilities.resize(size); // used for solver, set to appropriate size here to avoid recursively setting
}

// initialize function to fill in board with numbers
// 0 is used for empty space
// function is passed the ifstream class containing the file
void Board::initialize(ifstream& fin) {
	char reader; // char used to read inout from file
	int charReader; // int used to convert char to int
	if (fin.peek() == '\n') fin.get();
	for (int row = 0; row < size; row++) { // for the size (standard 9) of each row
		for (int column = 0; column < size; column++) { // for the size of each column (repeated for each row)
			reader = fin.get(); // read the next char in the file
			charReader = reader - '0'; // convert it to int by subtracting char zero from the read in char 
			if ((charReader > size) || (charReader < 0)) charReader = 0; // converts periods to 0s
			boardMatrix[row][column] = charReader; // sets next term in sudoku to read in value.
		}
	}
	return;
}

// prints the sudoku board
void Board::print() {
	for (int row = 0; row < size; row++) { // for each of  the 9 rows
										   // if statment only triggers for each square (3 for standard sudoku)
		if (row %squareSize == 0) {
			cout << " "; // outputse spacing to keep things in line with sudoku
			for (int y = 0; y < squareSize; y++) { // for number of squares
				cout << "   "; // output spacing between squares
				for (int x = 0; x < squareSize; x++) { // for number of terms 
					cout << "-  "; // print dash over each terms
				}
			}
			cout << endl;
		}
		for (int column = 0; column < size; column++) { // for each of the 9 columns (repeated for each row due to outer loop)
			if (column %squareSize == 0) cout << " | "; // prints out spacing char every size charecters 
			cout << " " << boardMatrix[row][column] << " "; // print the selected charecter
		}
		cout << " | " << endl; // prints line at the end of each row to make sudoku look nice
	}
	// same dash function as top of print fucntion to print dashes on bottom of square
	cout << " ";
	for (int y = 0; y < squareSize; y++) {
		cout << "   ";
		for (int x = 0; x < squareSize; x++) {
			cout << "-  ";
		}
	}
	cout << endl;
	return; // return
}

// initializes starting confliccts for sudoku board
bool Board::startConflicts() {
	int temp = 0;
	int squareFinder = 0; // used for the logic in determining which square to read from
	for (int row = 0; row < size; row++) { // for every column
		for (int column = 0; column < size; column++) { // for every row
			temp = boardMatrix[row][column]; // read in number at the specific point in the matrix
			if (temp != 0) { // if that number is not a zero
							 // below checks to ensure sudoku that was read in is valid
							 // if sudoku is already breaking a rule with given value, exception thrown
				if ((rowTruthTables[row][temp - 1] != 0) || (columnTruthTables[column][temp - 1] != 0) || (squareTruthTables[squareTruthSelect(row, column)][temp - 1] != 0)) {
					return true;
					// throw rangeError ("invalid sudoku);
				}
				rowTruthTables[row][temp - 1] = true; // set the bool for that row and number to true 
				columnTruthTables[column][temp - 1] = true; // set the bool for that column and number to true
				squareTruthTables[squareTruthSelect(row, column)][temp - 1] = true; // set the bool for that square and number to true
			}
		}
	}
	return  false;
}

//  determing which square to use
int Board::squareTruthSelect(int &row, int &column) {
	return ((row / squareSize) + (3 * (column / squareSize))); // puzzle is counted left to right, top to bottom
}

// prints out the conflict tables 
void Board::printConflicts() {
	cout << "row truth tables" << endl << endl; // prints header
	for (int outer = 0; outer < size; outer++) { // loops between the "size" bool tables
		for (int inner = 0; inner < size; inner++) { //loops throught the "size" bool values
			cout << rowTruthTables[outer][inner]; // print out the selected value
		}
		cout << endl;
	}

	// repeat above actions identically twice for the remaining tables
	cout << endl << "column truth tables" << endl << endl;
	for (int outer = 0; outer < size; outer++) {
		for (int inner = 0; inner < size; inner++) {
			cout << columnTruthTables[outer][inner];
		}
		cout << endl;
	}


	cout << endl << "square truth tables" << endl << endl;
	for (int outer = 0; outer < size; outer++) {
		for (int inner = 0; inner < size; inner++) {
			cout << squareTruthTables[outer][inner];
		}
		cout << endl;
	}
	cout << endl;
	return;
}

// cecks to see if cell value is 0
bool Board::isBlank(int row, int column) {
	if (boardMatrix[row][column] == 0) return true;
	else return false;
}

// gets the value stored at a cell
int Board::getCell(int row, int column) {
	return (boardMatrix[row][column]);
}

// sets the value in a cell
void Board::setCell(int row, int column, int valueToAdd) {
	boardMatrix[row][column] = valueToAdd;
}

// checks to see if all three truth tables allow for a value to get placed
bool Board::validCheck(int& row, int& column, int& value) {
	if (rowTruthTables[row][value - 1] == 0) { // if not limited by row
		if (columnTruthTables[column][value - 1] == 0) { // if not limited by column
			if (squareTruthTables[squareTruthSelect(row, column)][value - 1] == 0) return true;
		}
	}
	return false; // 1+ of the three truth tables read true
}

// updates the truth tables for a recently placed value
void Board::truthUpdater(int& row, int& column, int& value) {
	if (rowTruthTables[row][value-1] == true) { // if backtracking, setting terms back to 0
		rowTruthTables[row][value - 1] = 0; //set row truth to 0
		columnTruthTables[column][value - 1] = 0; // set column truth to 0
		squareTruthTables[squareTruthSelect(row, column)][value - 1] = 0; //set square truth to zero
	}
	else { // else if solving another square in the sudoku
		rowTruthTables[row][value - 1] = 1; //set row truth to one
		columnTruthTables[column][value - 1] = 1; // set column truth to one
		squareTruthTables[squareTruthSelect(row, column)][value - 1] = 1; // set square truth to one
	}
}

bool Board::isSolved() {
	for (int row = 0; row < size; row++) { // for every column
		for (int column = 0; column < size; column++) { // for every row
			if (boardMatrix[row][column] == 0) return false; // if there is an unsolved square, fail
		}
	}
	return true; // if all squares solved, return true.
}


// outer layer of loop, called recursively, that solves puzzle
// solves for the most constrained digit before recalling itself.
// deeper recursions return false if all possible digits are incorrect, returns true if puzzle is solved
bool Board::puzzleSolver() {
	if (isSolved()) return true; // exits if puzzle is solved, prevents extra layer of recursion after 81st term is solved
	recursions++; // increments the recursion counter every time the function is called
	int digit = digitToSolve(); // determines which of the 81  digits to solve for (returns 0-80 in 9x9) by checking which is the most constrained
	int rowSolve = digit%size; //  row digit is equal to the returned digit remainder when dividing by size
	int columnSolve = digit/size; // column is equal to the division
	bool exit = false; // bool used to return if puzzle gets solved
	int term; // used for readability

	// for loop checks for valid terms to be placed in the most constrained loop
	// guesses are sequential (0, 1, 2) and only placed if a valid term. Else, loop repeats.
	for (int i = 0; i < size; i++) {
		term = i + 1; // ensures sudoku solved 1-9 as opposed to 0-8
		if (validCheck(rowSolve, columnSolve, term) == true) { // if the tested term is allowed to be placed in the digit
			truthUpdater(rowSolve, columnSolve, term); // update truth tables with selected term
			boardMatrix[rowSolve][columnSolve] = term; // update the sudoku with the term
			exit = puzzleSolver(); // calls itself to solve for the next digit
			if (exit == true) return true; // used to exit all recursive functions sequentially if puzzle is solved deeper in recursion
			truthUpdater(rowSolve, columnSolve, term); // if term wound up being incorrect (all future digit solutions failed) remove truth table impact from the digit
			boardMatrix[rowSolve][columnSolve] = 0; // remove the digit from the matrix
		}
		
	}
	return (false); // return false if all possible digits are invalid, due to immediate or downstream solutions
	// this causes previously solved digit to itterate.
}

// returns the most constrained digit so the puzzle knows what to solve for
int Board::digitToSolve() {
	int solveThis[2] = { 0,0 }; // tracker of which digit is most constrained and how constrained that digit is
	int rowChoice; // which row digit is in
	int columnChoice; // which column digit is in
	int constraints = 0; // number of constraints on digit
	for (int i = 0; i < size*size; i++) { // checks how constrained each digit is
		rowChoice = i%size; // modulus of iterator gives row
		columnChoice = i / size; // division of itterator gives column
		if (boardMatrix[rowChoice][columnChoice] == 0) { //  if digit isnt solved
			constraints = 0; // set constraints to  0
			for (int x = 0; x < size; x++) { // for all possible digits (1-9)
				digitPossibilities[x] = false; // reset due to its being defined globally
				if (rowTruthTables[rowChoice][x] == true) { // if digit is constrained by row
					digitPossibilities[x] = true; // remove this term from digit possibilities
					constraints++; // increase number of constraints by 1
				}
				else if (columnTruthTables[columnChoice][x] == true) { // repeat for column if not constrained by row for this term
					digitPossibilities[x] = true;
					constraints++;
				}
				else if (squareTruthTables[squareTruthSelect(rowChoice, columnChoice)][x] == true) { // repeat by square if not constrained by either above
					digitPossibilities[x] = true;
					constraints++;
				}
			}
			if (constraints == size - 1) return (i); // if only one term is available for the square, return with that square immediatly
			if (constraints > solveThis[1]) { // else if digit is more constrained than all other solved for digit, set to sovlee this
				solveThis[0] = i; // 1st term is digit
				solveThis[1] = constraints; // 2nd term is how cconstrained that square is
			}
		}
	}
	return (solveThis[0]); // return which square should be solved for
}

// returns the number of recursions needed to solve the puzzle.
int Board::returnRecursions() {
	return(recursions);
}