/* Source filee for word list header
* contains all functions defined in wordlist.h
* each function contains description before lead of identifier
* BW 08OCT16
*/
#include "WordList.h"
#include <fstream> 
#include "d_except.h"
// WARNING: WORD LIST IS HARD-DEFINED IN CODE on line 18  <--------------------------------------------------

WordList::WordList() {} // bare constructor to initialize wordlist 

						// function to read in wordlist from txt file
						//opens file using fstream, reads until fstream fails to produce the next word, than closses file
						//uses predefined filename for list of words because prompt only specifies user input for grid filename
void WordList::input() {
	ifstream fin; // create the file  object  from fstream
	string filename = "wordList.txt"; //uses pre-defned file input name
									  //according to prompt, only matrix name should be read from keyboard
	fin.open(filename.c_str()); // opens the file
	if (!fin) throw rangeError("no wordList with that name");
	string x; // create variable for reading in words
	fin >> x; // read in first word
	while (fin >> x) { // while there are still words to be read into the file
		listOfWords.push_back(x); // add next word to vector
	}
	fin.close(); // close file
	return; // return
}

// function that sorts the word vector using insertion srt
// takes string vector from wordlist and performs insertion sort on it
void WordList::insertSort() {
	int z = 0; // define int for counter
	string key; // define string for sorting
	for (int y = 1; y < listOfWords.size(); y++) { // while words are still remaining in the list, iterate over the next word
		key = listOfWords[y]; // define key as the next unsorted word
		z = y - 1; // start cehcking if word is lower alphabetically at end of sorted list
		while (z > -1 && listOfWords[z] > key) { // while word is still lower than key alphabetically
			listOfWords[z + 1] = listOfWords[z];
			z--;
		}

		listOfWords[z + 1] = key;
	}
	return; // return
}

// handles mergesort
void WordList::mergeSortStarter() {
	mergeSortSplit(listOfWords, 0, (listOfWords.size() - 1));
}

//handles the splitting for mergesort by recursively calling itself
void WordList::mergeSortSplit(vector<string>& wordList, int first, int last) {
	if (first < last) {// makes sure vector isnt fully split
		int middle = (floor((last - first) / 2) + first); // splits vector in half
		mergeSortSplit(wordList, first, middle);// calls itself with first half of function
		mergeSortSplit(wordList, (middle + 1), last);// calls itself with second half of function
		mergeSortSort(wordList, first, middle, last);//sorts the two halves that are returned
	}
}

// handles the sorting portion of merge sort
void WordList::mergeSortSort(vector<string> &wordList, int first, int middle, int last) {
	vector<string> leftTempArray, rightTempArray; //creeate the temp arrays for the sorting to ouccr in
	int firstHalf = middle - first + 1; // firsthalf of array 
	int secondHalf = last - middle; // second half of array
	int x = 0;
	int y = 0;
	for (x = 0; x < firstHalf; x++) leftTempArray.push_back(wordList[x + 1]); // create first half of array from portion of main array
	leftTempArray.push_back(STRINGMAX);//set last value to string max
	for (int y = 0; y < secondHalf; y++) rightTempArray.push_back(wordList[middle + y + 1]);//create second half of array form portion of main array
	rightTempArray.push_back(STRINGMAX);//set last value to stringmax
	x = 0;
	y = 0;
	int sorter;
	for (sorter = first; sorter < last; sorter++) {// while all terms arn't sorted, add sorted terms to new array
		if (leftTempArray[x] < rightTempArray[y]) {
			wordList[sorter] = leftTempArray[x]; // modifies inital array with new correct locations
			x++;
		}
		else {
			wordList[sorter] = rightTempArray[y];// modifies inital array with new correct locations
			y++;
		}
	}
	return;
}

void WordList::quickSortStarter() { // launches quicksort from outside of class
	quickSortManager(listOfWords, 0, (listOfWords.size() - 1)); // calls first iteration of quicksort manager
}

int WordList::quickSortSorter(vector<string>& wordList, int start, int end) {
	static string pivot; // static to save on memory, help prevent stack overflow
	string temp; // used for replacement
	pivot = wordList[end]; // pivot is equal to last value
	int leftList = start - 1; // set leftlist to -1 of starting location on first run because it is incrmeented before value is used
	for (int vectorRunner = start; vectorRunner < end - 1; vectorRunner++) { // cycle through all of array that is passed
		if (wordList[vectorRunner] < pivot) { // if value is less than pivot
			leftList++;// incrment leftlist
			temp = wordList[leftList]; //  set temp pointer to value
			wordList[leftList] = wordList[vectorRunner]; // replaces leading larger value with smaller detected one
			wordList[vectorRunner] = temp; // replace the leading larger value at new position

		}
	}
	temp = wordList[end];// 4 lines set pivot into its proper positon
	wordList[end] = wordList[leftList + 1];
	wordList[leftList + 1] = pivot;
	//if (leftList +1 == end) return leftList;
	return(leftList + 1); // return the location of the pivot for next split
}

// handles the splitting up of the arrays for quicksorting
void WordList::quickSortManager(vector<string>& wordList, int start, int end) {
	int pivot = 0; // start with pivot as zero
	if (start < end) {
		pivot = quickSortSorter(wordList, start, end); // call the first time with full function, see where firs pivot lands
		quickSortManager(wordList, start, pivot);//recall the function with new first portion of array
		quickSortManager(wordList, pivot + 1, end);//recall the function with new second portion of array
	}
}

//handles the search for the needed words.
bool WordList::binarySearch(string wordToCheck) {
	static int left, right, mid; // ints to track position in word array
	left = 0;
	right = (listOfWords.size() - 1); // initally set to max
	while (left <= right) { // make sure list isn't exhausted without finding word.
		mid = (left + right) / 2; // calculate midpoint (floor default with c++)
		if (listOfWords[mid] == wordToCheck) { // if checked word is found, return true
			return true;
		}
		else if (listOfWords[mid] <= wordToCheck) left = mid + 1; // else check to see if word on the left or right of checked middle
		else right = mid - 1; // increment direction accordingly
	}
	return false;// return 0 if word not found
}

//overloaded print operator. added due to requirements but not called in function
ostream &operator << (ostream& ostr, const WordList& wordList) {
	for (int x = 0; x < wordList.listOfWords.size(); x++) { // for each value in the wordlist
		cout << wordList.listOfWords[x]; // print the given word
	}
	return ostr;
}
