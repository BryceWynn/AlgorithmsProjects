#pragma once
#include <iostream>

#define NUMBERSUITS 4 // used for function logic
#define NUMBERCARDS 13 // used for function logic

static char Suit[NUMBERSUITS] = { 'C', 'D', 'H', 'S' }; // set static to prevent linker errors, NUMBERSUITS used in definition to keep logic consistant
static char Number[NUMBERCARDS] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' }; // same as above


using namespace std;

class Card {
public:
	// constructors and deconstructors for the class
	Card();
	~Card();
	Card(char &cardNumber, char &cardSuit);
	void newCard(char &newNumber, char &newSuit);
	
	//set functions defined due to requirements but not used due to data being public
	void setSuit(char &changeSuit);
	void setNumber(char &changeNumber);
	void setPtr(Card *cardPtr);

	// friend function of ostream used for overloading operator, per requirements
	friend ostream& operator<< (ostream& ostr, const Card &nextCard);
	
	//get Functions defined but not used due to data being public for linked lists
	char getNumber();
	char getSuit();
	Card* getCardPtr();

	// data for linked list
	char suit;
	char number;
	Card *nextCard = nullptr;

private:

};