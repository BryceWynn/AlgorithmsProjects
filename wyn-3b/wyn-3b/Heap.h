/*Header File for Heap
* reads in the set of items given using infile
*can then sort the items  using minHeap or maxHeap
* BW 08OCT16
*/

#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

template <typename T>
class Heap {
public:
	Heap(); // empty initializers
	void input();
	void initializeMaxHeap();
	void maxHeapify();
	void buildMaxHeap(int position, int heapLength);
	void initializeMinHeap();
	void minHeapify();
	void buildMinHeap(int position, int heapLength);
	void heapSort(bool maxHeap);
	T wordReturner(int position);

private:
	vector<T> wordHeap;
};




template <typename T>
Heap<T>::Heap() {};// empty initalizer

template <typename T>
void Heap<T>::input() {
	ifstream fileIn; // create the file  object  from fstream
	string filename = "wordList.txt"; //uses pre-defned file input name
									  //according to prompt, only matrix name should be read from keyboard
	fileIn.open(filename.c_str()); // opens the file
	if (!fileIn) throw rangeError("no wordList with that name");
	T x; // create variable for reading in words
	fileIn >> x; // read in first word
	while (fileIn >> x) { // while there are still words to be read into the file
		wordHeap.push_back(x); // add next word to hashfield
	}
	fileIn.close(); // close file
	return; // return
}


//initalize max heap allows build max heap to be called outside of function
template <typename T>
void Heap<T>::initializeMaxHeap() {
	maxHeapify();// calls buildmax heap
	return;
}

// outer function that recurses to build the max heap
template <typename T>
void Heap<T>::maxHeapify() {
	int length = wordHeap.size(); // set int to length, starts halfway through the heap 
	for (int i = floor(length / 2); i > -1; i--) { // incrememnts along outside of heap starting halway throughh and decrementing to 1
		buildMaxHeap(i, length);// calls build max heap
	}
	return;
}

template <typename T>
void Heap<T>::buildMaxHeap(int position, int heapLength) { // heapLength ensures that it still works with sorting array

	if (heapLength == position * 2) return; // fringe case where no seeds
	T left = wordHeap[2 * position]; // otherwise set T to left ssed
	T right;
	if (heapLength == (position * 2 + 1)) right = ' '; // fringe case with only a left sided seed, low string that wont be moved
	else right = wordHeap[(2 * position) + 1]; // otherwise set t to right seed
	int largest = position; // set largest
	if ((wordHeap[largest] < left) && (left > right)) largest = 2*position; // if root is smaller than right, and right < left
	if ((wordHeap[largest] < right) && (left < right)) largest = 2*position+1; // if root < left & left  < right
	if (largest != position) { // if the root needs to be swapped
		T temp = wordHeap[largest];// create temp term of seed
		wordHeap[largest] = wordHeap[position]; // set root to seed
		wordHeap[position] = temp; // set seed to root
		if (largest < floor(heapLength / 2)) buildMaxHeap(largest, heapLength); // if not the last term, recurse
	}
	return;
}

// min heap works identically to max heap, just with the comparators all switched, and a different right fringe case
template <typename T>
void Heap<T>::initializeMinHeap() {
	buildMinHeap();
}

template <typename T>
void Heap<T>::minHeapify() {
	int length = wordHeap.length();
	int i;
	for (int i = floor(length / 2); i > 0; i--) {
		buildMinHeap(i, length);
	}
	return;
}

template <typename T>
void Heap<T>::buildMinHeap(int position, int heapLength) {
	if (heapLength == position * 2) return; // fringe case where no seeds
	T left = wordHeap[2 * position]; // otherwise set T to left ssed
	T right;
	if (heapLength == (position * 2 + 1)) right = 'a'; // fringe case with only a left sided seed, low string that wont be moved
	else right = wordHeap[(2 * position) + 1]; // otherwise set t to right seed
	int smallest = position; // set largest
	if ((wordHeap[smallest] > left) && (left < right)) smallest = 2 * position; // if root is smaller than right, and right < left
	if ((wordHeap[smallest] > right) && (left > right)) smallest = 2 * position + 1; // if root < left & left  < right
	if (smallest != position) { // if the root needs to be swapped
		T temp = wordHeap[smallest];// create temp term of seed
		wordHeap[smallest] = wordHeap[position]; // set root to seed
		wordHeap[position] = temp; // set seed to root
		if (smallest < floor(heapLength / 2)) buildMaxHeap(smallest, heapLength); // if not the last term, recurse
	}
	return;

}

//heapsorter, takes a bool to know if sorting a maxheap or a minheap
template <typename T>
void Heap<T>::heapSort(bool maxHeap) {
	T temp; // initialize temp varaible
	if (maxHeap == true) {
		for (int i = wordHeap.size() - 1; i > 0; i--) { // for every term in the heap
			temp = wordHeap[i]; // set last (smallest) value ot temp
				wordHeap[i] = wordHeap[1]; //move first (largest) value to last
				wordHeap[1] = temp; // move smallest value to top
			buildMaxHeap(1, i - 1); // re heap, with reduced size so as not to sort value
		}
		return; // already sorted, no need to go to else statement
	}
	else {
		for (int i = wordHeap.size() - 1; i > 0; i--) {
			temp = wordHeap[i];
				wordHeap[i] = wordHeap[1];
				wordHeap[1] = temp;
			buildMinHeap(1, i - 1);
		}
		return;
	}
}

template <typename T>
T Heap<T>::wordReturner(int position) {
	return (wordHeapp[position]);
}
