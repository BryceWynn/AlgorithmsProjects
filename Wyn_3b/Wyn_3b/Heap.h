/*Header File for Heap
* reads in the set of items given using infile
*can then sort the items  using minHeap or maxHeap
* BW 08OCT16
*/

#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Heap {
public:
	Heap(); // empty initializers
	void initializeMaxHeap();
	void maxHeapify();
	void buildMaxHeap(int position);
	void initializeMinHeap();
	void minHeapify();
	void buildMinHeap(int position);
	void heapSort(bool maxHeap);
	T wordReturner(int position);

private:
	vector<T> wordHeap;
};
