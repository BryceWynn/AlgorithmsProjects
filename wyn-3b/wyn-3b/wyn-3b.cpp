// contains main, findmatches, and search
// findmatches handles the binary search through the sorted word list
// search handles the setup and choice of sorting algorithm
// main runs the crossword program
// BW 10OCT16

#include "stdafx.h"
#include "Grid.h"
#include "WordList.h"
#include "time.h"
#include "HashTable.h"
#include "Heap.h"

#define SEARCHDIRECTIONS 8

void findMatches(WordList masterList, Grid masterGrid) {
	int dimension = masterGrid.columnReturner(); // determines how many iterations must be made
	int chars = 0; // used in inside for loops, defined outside to save multiple definitions
	string charsToSearch;
	int searchingX = 0;
	int searchingY = 0;
	// first two for loops cause function to cycle through each char as a starting point
	// third for loops cycles through the 8 directions words can be searched for
	// if a words is found, binary search returns true and the current set of chars is printed to the screen

	for (int xDimension = 0; xDimension < dimension; xDimension++) { // cycle through the rows
		for (int yDimension = 0; yDimension < dimension; yDimension++) { // cycle through the columns
			for (int z = 0; z < SEARCHDIRECTIONS; z++) { // cycle through the directions to search
				charsToSearch.clear(); // clear previous string
				searchingX = xDimension; // ensure search starts at starting position
				searchingY = yDimension; // same as above
				switch (z) { // switch case to handle directions

							 //each case handles one set of the directions that needs to be checked
							 // they add one char, than check for that word and then increment in a given direction
							 // loop then cycles through all 8 case statements for all 8 directions to search

				case 0: // NW case
					for (chars = 0; chars < dimension; chars++) { // increments over all total lengths of words
						charsToSearch += masterGrid.charReturner(searchingX, searchingY); // adds one more char to the search
						if (masterList.binarySearch(charsToSearch)) cout << charsToSearch << endl; // checks the dict to see if it is an existing word
						searchingX--; // decrements X
						if (searchingX < 0) searchingX = dimension - 1; //ensures that if x is set to a negative, it is turned t0 max instead
						searchingY--; // decrements y
						if (searchingY < 0) searchingY = dimension - 1; // same as above
					}
					break;

					// remaining cases all handled in a similar manner, just with some being incremented instead of decremented or keft alone
					// also for incrementing values, check is to see if it is equal to dimension than set to 1/

				case 1: // W case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.binarySearch(charsToSearch)) cout << charsToSearch << endl;
						searchingY--;
						if (searchingY < 0) searchingY = dimension - 1;
					}
					break;

				case 2: // SW case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.binarySearch(charsToSearch)) cout << charsToSearch << endl;
						searchingY--;
						if (searchingY < 0) searchingY = dimension - 1;
						searchingX++;
						if (searchingX >= dimension) searchingX = 0;
					}
					break;

				case 3: // S case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.binarySearch(charsToSearch) == true) cout << charsToSearch << endl;
						searchingX++;
						if (searchingX >= dimension) searchingX = 0;
					}
					break;

				case 4: // SE case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.binarySearch(charsToSearch)) cout << charsToSearch << endl;
						searchingY++;
						if (searchingY >= dimension) searchingY = 0;
						searchingX++;
						if (searchingX >= dimension) searchingX = 0;
					}
					break;

				case 5: // E case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.binarySearch(charsToSearch)) cout << charsToSearch << endl;
						searchingY++;
						if (searchingY >= dimension) searchingY = 0;
					}
					break;

				case 6: // NE case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.binarySearch(charsToSearch)) cout << charsToSearch << endl;
						searchingY++;
						if (searchingY >= dimension) searchingY = 0;
						searchingX--;
						if (searchingX < 0) searchingX = dimension - 1;
					}
					break;

				case 7: // N case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.binarySearch(charsToSearch)) cout << charsToSearch << endl;
						searchingX--;
						if (searchingX < 0) searchingX = dimension - 1;
					}
					break;
				}
			}
		}
	}
	getchar();
	return;
}

void findMatches(HashTable<string> masterList, Grid masterGrid) {
	int dimension = masterGrid.columnReturner(); // determines how many iterations must be made
	int chars = 0; // used in inside for loops, defined outside to save multiple definitions
	string charsToSearch;
	int searchingX = 0;
	int searchingY = 0;
	if (masterList.inList(charsToSearch) == true) chars = 1;
	// first two for loops cause function to cycle through each char as a starting point
	// third for loops cycles through the 8 directions words can be searched for
	// if a words is found, binary search returns true and the current set of chars is printed to the screen

	for (int xDimension = 0; xDimension < dimension; xDimension++) { // cycle through the rows
		for (int yDimension = 0; yDimension < dimension; yDimension++) { // cycle through the columns
			for (int z = 0; z < SEARCHDIRECTIONS; z++) { // cycle through the directions to search
				charsToSearch.clear(); // clear previous string
				searchingX = xDimension; // ensure search starts at starting position
				searchingY = yDimension; // same as above
				switch (z) { // switch case to handle directions

							 //each case handles one set of the directions that needs to be checked
							 // they add one char, than check for that word and then increment in a given direction
							 // loop then cycles through all 8 case statements for all 8 directions to search

				case 0: // NW case
					for (chars = 0; chars < dimension; chars++) { // increments over all total lengths of words
						charsToSearch += masterGrid.charReturner(searchingX, searchingY); // adds one more char to the search
						if (masterList.inList(charsToSearch)) cout << charsToSearch << endl;																  //if (masterList.inList(charsToSearch)) cout << charsToSearch << endl; // checks the dict to see if it is an existing word
						searchingX--; // decrements X
						if (searchingX < 0) searchingX = dimension - 1; //ensures that if x is set to a negative, it is turned t0 max instead
						searchingY--; // decrements y
						if (searchingY < 0) searchingY = dimension - 1; // same as above
					}
					break;

					// remaining cases all handled in a similar manner, just with some being incremented instead of decremented or keft alone
					// also for incrementing values, check is to see if it is equal to dimension than set to 1/

				case 1: // W case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.inList(charsToSearch)) cout << charsToSearch << endl;
						searchingY--;
						if (searchingY < 0) searchingY = dimension - 1;
					}
					break;

				case 2: // SW case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.inList(charsToSearch)) cout << charsToSearch << endl;
						searchingY--;
						if (searchingY < 0) searchingY = dimension - 1;
						searchingX++;
						if (searchingX >= dimension) searchingX = 0;
					}
					break;

				case 3: // S case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.inList(charsToSearch) == true) cout << charsToSearch << endl;
						searchingX++;
						if (searchingX >= dimension) searchingX = 0;
					}
					break;

				case 4: // SE case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.inList(charsToSearch)) cout << charsToSearch << endl;
						searchingY++;
						if (searchingY >= dimension) searchingY = 0;
						searchingX++;
						if (searchingX >= dimension) searchingX = 0;
					}
					break;

				case 5: // E case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.inList(charsToSearch)) cout << charsToSearch << endl;
						searchingY++;
						if (searchingY >= dimension) searchingY = 0;
					}
					break;

				case 6: // NE case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.inList(charsToSearch)) cout << charsToSearch << endl;
						searchingY++;
						if (searchingY >= dimension) searchingY = 0;
						searchingX--;
						if (searchingX < 0) searchingX = dimension - 1;
					}
					break;

				case 7: // N case
					for (chars = 0; chars < dimension; chars++) {
						charsToSearch += masterGrid.charReturner(searchingX, searchingY);
						if (masterList.inList(charsToSearch)) cout << charsToSearch << endl;
						searchingX--;
						if (searchingX < 0) searchingX = dimension - 1;
					}
					break;
				}
			}
		}
	}
	getchar();
	return;
}

// handles game setup and sorting algorithm choice
void search(bool input1, int input2) {
	WordList masterList; // wordlist object used
	Grid masterGrid; // grid object used
	HashTable<string> hashList;
	Heap<string> heapList;
	if (!input1) {
		if (input2 != 4) { masterList.input(); } // function to read in words from file
	}
	if (input2 == 4) { heapList.input(); }
	else hashList.input();
	clock_t startTime, endTime; // clock for processing time
	long elapsedTotal; // total time elapsed
	long elapsed; // elapsed for each section
	startTime = clock(); // set start time
	if (!input1){
		switch (input2) { // switch statement to handle which sorting method is used
		case 1:
			masterList.insertSort(); // insertion sort
			break;

		case 2:
			masterList.quickSortStarter();// quicksort
			break;

		case 3:
			masterList.mergeSortStarter();//mergesort
			break;

		case 4:
			heapList.initializeMaxHeap();
			heapList.heapSort(1); // max heapsort
		}
	}
	elapsed = startTime - clock(); // set end time
	elapsedTotal = elapsed / CLOCKS_PER_SEC; // calculate elapsed time
	cout << "sortingTime is equal to " << elapsedTotal << " seconds " << endl; // print it
	string fileName;// create string for file selection
	cout << "please input name of grid file to use" << endl; // outputrequest for file
	cin >> fileName;// readin request for file
	try {
		masterGrid.fileReader(fileName); // read grid
		startTime = clock(); // starttimer
		if (!input1) findMatches(masterList, masterGrid); // look for matches in grid
		else findMatches(hashList, masterGrid);
		elapsed = startTime - clock(); // end timer

		cout << "time to find words was " << elapsed / CLOCKS_PER_SEC << "seconds" << endl; // print elapsed time
		elapsedTotal += elapsed / CLOCKS_PER_SEC;
		cout << "total time was " << elapsedTotal << "seconds" << endl;
	}
	catch (rangeError &ex) {
		cout << "operation error " << endl << ex.what() << endl << endl;
	}
	return; // return to main
}


//launches all necessary functions
int main()
{
	bool correctIn = false;
	cout << "Please select desired storage method" << endl
		<< "0 for WordList, 1 for HashTable" << endl;
	bool input1; // could be bool
	cin >> input1;
	int input2 = 1;
	if (!input1) {
		cout << "Please select desired sorting function" << endl
			<< "1 for insertion, 2 for quicksort, 3 for mergesort, 4 for heap" << endl;
		cin >> input2; // take in user choice
	}
	try {
		if (input2 != 1) {
			if (input2 != 2) {
				if (input2 != 3) {
					if  (input2 != 4) throw rangeError("invalid entry for sorting selection"); // throw error for invalid input
				}
			}
		}
		search(input1, input2); // launch function to solve
	}
	catch (rangeError &ex) {
		cout << ex.what() << endl << endl;
	}
	getchar();
}
