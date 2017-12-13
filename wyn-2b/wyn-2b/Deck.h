/*Deck Header for project 2b
* contains the declarations for all required functions
*also uses const NUMBEROFDECKS to allow deck amount to be changed if need be
* BW 03OCT16
*/

#pragma once
#include "Card.h"
#include <iostream>

using namespace std;
#define NUMBEROFDECKS 1 // allows several decks to be created and shuffled at once

class Deck {
public:
	Deck(); // basic constructor
	Deck(char &cardNumber, char &cardSuit); // construcctor that declares the first card
	Deck(int numberOfDecks); // constructor that produces a sequential deck of cards
	void operator= (const Deck &deckToCopy);	// overlaoded equal operator
	~Deck(); // deconstructor
	Card deal(); // function to return top card by value than delete it
	void replace(Card cardByValue); // adds a card to the end of the deck
	void cardPrinter(); // prints every card in the deck, not currently used in iteration for 2b
	void shuffle(); // function to randomize the order of the cards

private:
	Card *topDeck = nullptr; // ptr to top of deck
};