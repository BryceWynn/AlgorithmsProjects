// contains all functions used for heap sorting of new words
// capable of creating max or min heap
// heapsorter deteccts whicch type of heap than sorts words accordingly
// also contains get unction to return value
// BW 10OCT16

#include "stdafx.h"
#include "Heap.h"
template <typename T>

Heap<T>::Heap() {};

template <typename T>
void Heap<T>::initializeMaxHeap() {
	buildMaxHeap();
}

template <typename T>
void Heap<T>::maxHeapify() {
	int length = wordHeap.length();
	for (int i = floor(length / 2); i > 0; i--) {
		buildMaxHeap(i);
	}
	return;
}

template <typename T>
void Heap<T>::buildMaxHeap(int position) {
	
	if (wordHeap.length == position * 2) return; // fringe case where no seeds
	T left = wordHeap[2 * position]; 
	if (wordHeap.length == (position *2 + 1)) right = 'a' // fringe case with only a left sided seed
	else T right = wordHeap[(2 * position) + 1];
	int largest = i;
	if (wordHeap[i] < left && left < right) largest = right;
	else if (wordHeap[i] < right && left > right) largest = left;
	if (largest != i){
		T temp = wordHeap[i];
		wordHeap[i] = left;
		wordHeap[i * 2] = temp;
		if (largest < floor(wordHeap.length() / 2)) buildMaxHeap(length); // if not the last term, recurse
	}
	return;
}


template <typename T>
void Heap<T>::initializeMinHeap() {
	buildMinHeap();
}

template <typename T>
void Heap<T>::minHeapify() {
	int length = wordHeap.length();
	for (int i = floor(length / 2); i > 0; i--) {
		buildMinHeap(i);
	}
	return;
}

template <typename T>
void Heap<T>::buildMinHeap(int position) {
	if (wordHeap.length == position * 2) return; // fringe case where no seeds
	T left = wordHeap[2 * position]; 
	if (wordHeap.length == (position *2 + 1)) T right = 'zz' // fringe case with only a left sided seed
	else T right = wordHeap[(2 * position) + 1];
	int smallest = i;
	if (wordHeap[i] > left && left > right) largest = right;
	else if (wordHeap[i] > right && left < right) largest = left;
	if (smallest != i){
		T temp = wordHeap[i];
		wordHeap[i] = left;
		wordHeap[i * 2] = temp;
		if (largest < floor(wordHeap.length() / 2)) buildMaxHeap(length); // if not the last term, recurse
	}
	return;

}

template <typename T>
void Heap<T>::heapSort(bool maxHeap) {
	T temp;
	if (maxHeap == true) {
		for (int heapSize = wordHeap.size() - 1; i > 0; i--) {
			temp = wordHeap[i]
			wordHeap[i] = wordHeap[1]
			wordHeap[k] = temp;
			buildMaxHeap(1);
		}
		return; // already sorted, no need to go to else statement
	}
	else {
		for (int heapSize = wordHeap.size() - 1; i > 0; i--) {
			temp = wordHeap[i]
			wordHeap[i] = wordHeap[1]
			wordHeap[k] = temp;
			buildMinHeap(1);
		}
		return; 
	}
}

template <typename T>
T Heap<T>::wordReturner(int position) {

}
