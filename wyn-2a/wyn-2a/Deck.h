#pragma once
#include "Card.h"
#include <iostream>
#define NUMBEROFDECKS 1 // allows several decks to be created and shuffled at once
using namespace std;

class Deck {
public:
	Deck();
	Deck(char &cardNumber, char &cardSuit);
	Deck(int numberOfDecks);
	~Deck();
	void cardPrinter();


private:
	Card *topDeck = nullptr;
};