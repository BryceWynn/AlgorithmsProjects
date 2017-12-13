/* Deck Class functions for flip card games
*controls constructor for a linked list where the head is stored inside deck
*utilizes an overloaded constructor in card to print deck
*also contains several overloaded constructors/overloaded destructor to ensure no memory leaks
*BW 26Sep16
*
*Modified for assignment 2B, with added copy constructor, destructor, and overloaded assignment operator
*also contains deal, replace, and shuffle functions to manipulate the card quantitity and order
*BW 02OCT16
*/

#define NUMBEROFSHUFFLES 3 // number of times to shuffle 
#include "Deck.h"
#include <vector> // used for shuffle function to randomize pointers, randomizing card order
#include <algorithm> // used for random_shuffle, which is what randomizes the vector of pointers
#include <ctime> // uused for the seed for the number shuffler

#include "d_except.h"

#pragma once
using namespace std;

Deck::Deck() {

}

// deck constructor that sets the card at top deck
Deck::Deck(char &cardNumber, char &cardSuit) {
	topDeck = new Card(cardNumber, cardSuit); // creates first ard in deck using card constructor with passed values, ptr of that card is null
}

Deck::Deck(int numberOfDecks) {
	// setup terms used in for loop
	int x = 0;
	Card *tempPtr = nullptr;

	// 3 iterating for loops
	// the first is for number of decks (1 for this project) the 2nd for the suit, and the third for the card number
	for (int deckNumber = 0; deckNumber < numberOfDecks; deckNumber++) { // check for proper number of decks
		for (int currentSuit = 0; currentSuit < NUMBERSUITS; currentSuit++) { // check for full number integration (2-A)
			for (int currentNumber = 0; currentNumber < NUMBERCARDS; currentNumber++) { // check for all 4 suits
				if (topDeck == nullptr) { // if topDeck is null (first term)
					topDeck = new Card(Number[currentNumber], Suit[currentSuit]); //create head of linked list
					currentNumber++;// iterate once
					topDeck->nextCard = new Card(Number[currentNumber], Suit[currentSuit]); // create second term in linked list
					tempPtr = topDeck->nextCard; // set that terms pointer to temp pointer
				}
				else {
					tempPtr->nextCard = new Card(Number[currentNumber], Suit[currentSuit]); // set the pointer at tempPtr equal to a new card 
					tempPtr = tempPtr->nextCard; //set tempPtr to the address of that new Card

				}
			}
		}
	}
}

void Deck::operator=(const Deck &deckToCopy) {
	// creates a copy of an existing deck into a new deck
	// uses two pointers (ptr) one tracking the old deck, and a second incrementing along the new deck
	// not used for game, but function requested as  part of assignment

	Card *tempPtrDeckToCopy; //ptr tracking the linked list of the deck to copy
	Card *tempPtrNewDeck; // ptr tracking the linked list of the new deck 
	tempPtrDeckToCopy = deckToCopy.topDeck; // tempPtr sets its address to the head of the list to be copied
	
	// note: no catch for thrown error as function is currently unused, catch must be added if function is implemented
	if (tempPtrDeckToCopy == nullptr) throw rangeError("Deck to copy was non-existant"); // throws error if function is passed null value 
	topDeck = new Card(*tempPtrDeckToCopy); // creates a new card with the same information as the head of the old head, and makes it first card of new deck
	tempPtrDeckToCopy = deckToCopy.topDeck->nextCard; // sets tmpPtr to second card in deck
	if (tempPtrDeckToCopy == nullptr) return; // exits if only one card Deck
	topDeck->nextCard = new Card(*tempPtrDeckToCopy); // creates second card in new deck passed on passed ptr
	tempPtrNewDeck = topDeck->nextCard->nextCard; // sets tempPtr equal to the pointer of the second card in the deck (first non topcard ptr)
	tempPtrDeckToCopy = tempPtrDeckToCopy->nextCard; // incrememnts temp 
	if (tempPtrDeckToCopy == nullptr) return; // exits if only two cards in deck
	while (tempPtrDeckToCopy != nullptr) { // while there are cards remaining in deck
		tempPtrNewDeck->nextCard = new Card(*tempPtrDeckToCopy); // create a new card for new deck that has same value as old deck
		tempPtrNewDeck = tempPtrNewDeck->nextCard; // increment pointer of old deck to next card
		tempPtrDeckToCopy = tempPtrDeckToCopy->nextCard; // increment pointer of new  deck to next pointer
	}
	return; // end function
}

// deconstructor for deck
Deck::~Deck() {
	//utilizes two ptrs to track through deck while deleting all the values
	Card* tempPtr; // ptr 1
	Card* tempPtrTracker; // ptr 2
	tempPtrTracker = topDeck; //set ptr1 to topdeck
	while (tempPtrTracker != nullptr) { // loops until all cards are deleted
		tempPtr = tempPtrTracker->nextCard; // set ptr 2 equal to next card in deck
		delete tempPtrTracker;// delete card ptr1 is pointing to
		tempPtrTracker = tempPtr; // set ptr 1 equal to ptr 2
	}
}

Card Deck::deal() {
	// function returns the top card of the deck by value
	//then sets the top of the deck to the following card'
	// lastly, it deletes  the old top card of the deck to prevent a memory leak

	Card cardToPass(topDeck->number,topDeck->suit );// creates card to return at end of function
	Card* cardToDelete;//  creates a pointer to allow the top of the deck to be passed properly and still delted
	cardToDelete = topDeck; // stores the address of the top card for future deltion
	topDeck = topDeck->nextCard; // sets the top of the deck to the next card
	delete cardToDelete; // deletes the returned card 
	return (cardToPass); //  returns the card by value
}

void Deck::replace(Card cardByValue) {
	// function that is passed a card by value and then adds it to the back of the deck
	//not used for playgame, but included due to assignment requirements
	// tracks through the linked list until it finds the end of the list, and adds the passed card to the list

	Card * tempPtr; // tracks to the end of the list
	Card *  tempPtrTracker; // stays one behind tempPtr, so that it is pointing to the last ccard when tempPtr reaches the end of the list
	tempPtr = topDeck; // sets tempPtr to the top of the deck
	if (tempPtr == nullptr) { // checks if there is no deck
		topDeck = &cardByValue; // if there is no deck, make the passed value the top card, than return
		return;
	}
	tempPtrTracker = tempPtr; // sets tempTracker to the top of the deck
	tempPtr = topDeck->nextCard; // sets tempPtr equal to the address of the second card
	while (tempPtr != nullptr) { // while tmpPtr is not at the end of the deck
		tempPtrTracker = tempPtr; // set tracker to tempptr
		tempPtr = tempPtr->nextCard; // increment tmpPtr through the linked list
	}
	//once tempPtr is at the end of the list
	tempPtrTracker->nextCard = &cardByValue; // set the last cards pointer to the new address passed by value
	return; // exit function
}

void Deck::cardPrinter() {
	Card *cardPtr = nullptr; // create tempPtr
	cardPtr = topDeck;// set cardPtr equal to the top of the deck
	while (cardPtr != nullptr) { // while the Deck is not at its last term
		cout << *cardPtr; // use overloaded function to print out card values
		cardPtr = cardPtr->nextCard; // set cardPtr to the ptr to the next card
	}
}

void Deck::shuffle() {
	// randomizes the order of all pointers in Deck, randomizing the card order

	srand(unsigned(time(0))); // seed for shuffler based off computer clock
	vector<Card*> cardArray; // vector of card pointers that will be shuffled
	Card* tempPtr = topDeck; // ptr used for creating and deconstructing the random list
	Card* tempPtrTracker; // used to ensure proper pointer is always replaced

	cardArray.push_back(tempPtr); //puts first card into vector
	tempPtr = topDeck->nextCard; // sets tempPtr to second card

	while (tempPtr != nullptr) { //while there are still cards reamining in the deck
		cardArray.push_back(tempPtr); // assign the next card to the vector
		tempPtr = tempPtr->nextCard; // set tempPtr to the next card
	}
	// shuffles the array of pointers the designated number of times in the prompt, using the shuffle function from random
	for (int x = 0; x < NUMBEROFSHUFFLES; x++) {
		random_shuffle (cardArray.begin(), cardArray.end());
	}

	tempPtr = cardArray.back(); // sets temp ptr to the back of the vector
	topDeck = tempPtr; // sets topDeck (start of the linked list) to the first pointer 
	cardArray.pop_back(); // removed first pointer from vector
	tempPtr = cardArray.back(); // sets temptr to new last ptr in vector (initially second to last ptr)
	topDeck->nextCard = tempPtr; // sets pointer of topDeck to new card
	tempPtrTracker = tempPtr; // sets tmpPtrTracker to tmpPtr before incrementing tmpPtr;
	cardArray.pop_back();// removes second pointer from vector

	while (cardArray.size() != 0) { // while there are still pointers in the vector
		tempPtr = cardArray.back(); // set tempPtr to new next vaalue in vector
		tempPtrTracker->nextCard = tempPtr; // set the pointer of the current card to that new next card
		cardArray.pop_back(); // remove past value from vector
		tempPtrTracker = tempPtr;
	}
}