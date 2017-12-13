/* Deck Class functions for flip card games
*controls constructor for a linked list where the head is stored inside deck
*utilizes an overloaded constructor in card to print deck
*also contains several overloaded constructors/overloaded destructor to ensure no memory leaks
* BW 26Sep16
*/

#include "Deck.h"
#pragma once
using namespace std;

Deck::Deck() {

}

Deck::Deck(char &cardNumber, char &cardSuit) {
	topDeck = new Card(cardNumber, cardSuit);
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

Deck::~Deck() {
	delete topDeck;
}

void Deck::cardPrinter() {
	Card *cardPtr = nullptr; // create tempPtr
	cardPtr = topDeck;// set cardPtr equal to the top of the deck
	while (cardPtr != nullptr) { // while the Deck is not at its last term
		cout << *cardPtr; // use overloaded function to print out card values
		cardPtr = cardPtr->nextCard; // set cardPtr to the ptr to the next card
	}
}