/*Header File for HashTable
* adds/deletes items from a list. can return a bool to check if an item is in a list
* also contains a function (unused) to return the hash value of an item
* BW 13OCT16
*
*Function files moved below ehader file as opposed to in cpp file
* Fixes several linker errors and allows function to run properly
*BW 18OCT16
*/


#pragma once
#include <functional>
#include <vector>
#include "d_except.h"
#include <string>
#include <fstream>

template <typename T>
class HashTable {
private:
	int size = 719;// size of has table, could be larger if lower overlap is desired, currently approx 120 words/vector
	vector < vector<T> >hashTable; // stores hash table
	hash<T> hasher;// hash class for hashing whatever datatype is used
	int hashValue = 0; // used in enough options that defining here makes sense
public:
	void input(); // reads data into hashtable	
	void addItem(T itemToAdd);// adds data t hashtable
	void deleteItem(T itemToDelete); // removes data from hashtable
	bool inList(T itemToCheck); // checks to see if string is in hashtable
	int hash(T itemToHash); // returns hash value of item (unused)

};

// takes input function from wordlist and slightly modifies it to fit hash archetype
template <typename T>
void HashTable<T>::input() {
	hashTable.resize(size);
	ifstream fileIn; // create the file  object  from fstream
	string filename = "wordList.txt"; //uses pre-defned file input name
									  //according to prompt, only matrix name should be read from keyboard
	fileIn.open(filename.c_str()); // opens the file
	if (!fileIn) throw rangeError("no wordList with that name");
	T x; // create variable for reading in words
	fileIn >> x; // read in first word
	while (fileIn >> x) { // while there are still words to be read into the file
			addItem(x); // add next word to hashfield
	}
	fileIn.close(); // close file
	return; // return
}

// function to add items
template <typename T>
void HashTable<T>::addItem(T itemToAdd) { // gets passed string to add
	hashValue = hasher(itemToAdd)%size; // determines hash value of string
	hashTable[hashValue].push_back(itemToAdd); // places into appropriate vector
}

// function to delete items
template <typename T>
void HashTable<T>::deleteItem(T itemToDelete) { // get passed item to remove
	hashValue = hasher(itemToDelete) % size;// hashes item to remove
	int temp = hashTable[hashValue].sizeof(); // takes size of vector of that particular hash
	for (int i = 0; i < temp; i++) { // increments over that vector until item is found
		if (hashTable[hashValue][i] == itemToDelete) { // if item is found
			hashTable[hashValue][i] = hashTable[hashValue][temp - 1]; // swap last item with this item
			hashTable[hashValue].pop_back(); // remove duplicate last item
			return; // return
		}
	}
	throw rangeError("no object to delete"); // throw error if item to delte is not in list
	return;
}

// function to check if item is in table
//identical to delete item, but returns a 1 if item is found and a 0 otherwise
template <typename T>
bool HashTable<T>::inList(T itemToCheck) {
	hashValue = hasher(itemToCheck)%size;
	for (int i = 0; i < hashTable[hashValue].size(); i++) {
		if (hashTable[hashValue][i] == itemToCheck) {
			return true;
		}
	}
		return false;
}

//returns the hash value of the item given
template <typename T>
int HashTable<T>::hash(T itemToHash) {
	return (hasher(itemToHash)%size);//returns the hashvalue of the given item, calculates in same line
}

