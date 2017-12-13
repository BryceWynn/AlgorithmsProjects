/*Header File for HashTable
* adds/deletes items from a list. can return a bool to check if an item is in a list
* also contains a function (unused) to return the hash value of an item
* BW 08OCT16
*/


#pragma once
#include <functional>
#include <vector>
#include "d_except.h"
#include <string>

template <typename T>
class HashTable {
private:
	vector < vector<T> >hashTable;
	hash<T> hasher;
	int hashValue = 0; // used in enough options that defining here makes sense
public:
	void addItem(T itemToAdd);
	void deleteItem(T itemToDelete);
	bool inList(T itemToCheck);
	int hash(T itemToHash);

};

// contains all functions used for HashTable
// BW 16OCT16
#include "stdafx.h"
#include "HashTable.h"
#include <string>



template <typename T>
void HashTable<T>::addItem(T itemToAdd) {
	hashValue = hasher(itemToAdd) % size;
	hashTable[hashValue].push_back(itemToAdd);
}

template <typename T>
void HashTable<T>::deleteItem(T itemToDelete) {
	hashValue = hasher(itemToDelete) % size;
	int temp = hashTable[hashValue].sizeof();
	for (int i = 0; i < temp; i++) {
		if (hashTable[hashValue][i] == itemToDelete) {
			hashTable[hashValue][i] = hashTable[hashValue][temp - 1];
			hashTable[hashValue].pop_back();
			return;
		}
	}
	throw rangeError("no object to delete");
	return;
}

template <typename T>
bool HashTable<T>::inList(T itemToCheck) {
	hashValue = hasher(itemToCheck) % size;
	for (int i = 0; i < hashTable[hashValue].size(); i++) {
		if (hashTable[hashValue][i] == itemToCheck) {
			return true;
		}
	}
	else {
		return false;
	}
}

template <typename T>
int HashTable<T>::hash(T itemToHash) {
	return (hasher(itemToHash) % size);
}