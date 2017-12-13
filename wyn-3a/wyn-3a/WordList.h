/*Header File for wordlist
* reads in the set of words given using infile
*can then sort the list using three different functions
* also contains a function for binary sorting of an input
* BW 08OCT16
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#define STRINGMAX "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"

using namespace std;

class WordList {
public:
	WordList(); // bare constructor
	void input(); // reads in the .txt file of words
	void insertSort(); // insertion sorting method for vector
	void quickSortStarter(); // triggers quick sort
	int quickSortSorter(vector<string>& wordList, int start, int end); // quicksorting method for vector that does the splitting
	void quickSortManager(vector<string>& wordList, int first, int last); //  quicksorting method for vector that does the
	void mergeSortStarter(); // triggers merge sort
	void mergeSortSplit(vector<string>& wordList, int first, int last); // manages both merge functions
	void mergeSortSort(vector<string> &wordlist, int first, int middle, int last); // manages the recombination of the merge sort function 
	bool binarySearch(string wordToCheck); //binary search function, prints matching string in function, returns a bool to allow for count of total words found
	friend ostream& operator << (ostream& ostr, const WordList &wordList); // overloaded print operator for wordlist

private:
	vector<string> listOfWords;
};